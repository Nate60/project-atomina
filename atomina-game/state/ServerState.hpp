#pragma once
#include <atomina.hpp>
#include "../GameEnums.hpp"

class ServerState: public ATMA::BaseState, public ATMA::ObjectEventListener
{
public:
    ATMA::ATMAContext &ctx = ATMA::ATMAContext::getContext();

    ServerState(): BaseState() {}

    virtual ~ServerState() {}

    /**
     * stub implementation of activate function
     */
    virtual void activate() override
    {
        m_active = true;
    }

    /**
     * stub implementation of deactivate function
     */
    virtual void deactivate() override {}

    virtual void notify(const ATMA::ObjectEventContext &l_e) override
    {
        if(l_e.m_objectEventType != ATMA::ObjectEventType(ATMA::ObjectEvent::Network))
            return;
        ATMA_ENGINE_TRACE("handling event in server state");
        unsigned int msgType = l_e.m_properties.getAs<unsigned int>("msgType");
        ATMA_ENGINE_TRACE("getting conn id from object event message");
        std::optional<unsigned int> connId = l_e.m_properties.getAs<std::optional<unsigned int>>("connId");
        ATMA_ENGINE_TRACE("got conn id from object message");
        switch(msgType)
        {
        case static_cast<unsigned int>(ATMA::NetworkMessageEnum::PORT_REQUEST):
            {
                int i = 0;
                std::map<std::string, std::any> msgEntries{};
                for(; i < m_ports.size(); i++)
                {
                    msgEntries["port" + std::to_string(i)] = std::pair<unsigned char, std::any>{
                        ATMA::NetworkMessageValueType(ATMA::NetworkMessageValueEnum::SHORT), (short)-1 // occupied
                    };
                    std::pair<unsigned char, std::any> pair{
                        ATMA::NetworkMessageValueType(ATMA::NetworkMessageValueEnum::SHORT),
                        (short)m_ports.size() // empty
                    };
                    ATMA::Props p{{{"port", pair}}};
                    ATMA::NetworkMessage broadcast{ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::PORT_JOIN), p};
                    ctx.netManager.sendMessage(broadcast, m_ports[i]);
                }
                m_ports.emplace_back(connId);
                msgEntries["port" + std::to_string(i)] = std::pair<unsigned char, std::any>{
                    ATMA::NetworkMessageValueType(ATMA::NetworkMessageValueEnum::SHORT), (short)1 // port to be filled
                };
                ++i;
                for(; i < MAX_PORTS; i++)
                {
                    msgEntries["port" + std::to_string(i)] = std::pair<unsigned char, std::any>{
                        ATMA::NetworkMessageValueType(ATMA::NetworkMessageValueEnum::SHORT), (short)0 // empty
                    };
                }
                ATMA::Props p{msgEntries};
                ATMA_ENGINE_INFO("User has requested port data");
                ATMA::NetworkMessage resp{ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::PORT_RESPONSE), p};
                ctx.netManager.sendMessage(resp, connId);
            }
            break;
        case static_cast<unsigned int>(ATMA::NetworkMessageEnum::STATE_CHANGE):
            {
                ATMA::Props p{
                    {{"state",
                      std::pair<unsigned char, std::any>{
                          ATMA::NetworkMessageValueType(ATMA::NetworkMessageValueEnum::UNSIGNEDINT),
                          l_e.m_properties.getAs<unsigned int>("state")
                      }}}
                };
                ATMA::NetworkMessage nm{ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::STATE_CHANGE), p};
                ctx.netManager.broadcastMessage(nm);
            }
            break;
        case static_cast<unsigned int>(GameNetMessageEnum::PLAYER_CHOICE):
            {
                m_playerChoices.emplace_back(std::make_pair(connId, l_e.m_properties.getAs<unsigned int>("choice")));
                if(m_playerChoices.size() > 1)
                {
                    ATMA::Props left{
                        {
                            {
                                "you",
                                std::pair<unsigned char, std::any>{
                                    ATMA::NetworkMessageValueType(ATMA::NetworkMessageValueEnum::UNSIGNEDINT),
                                    m_playerChoices[0].second
                                }
                            },
                            {
                                 "them",
                                 std::pair<unsigned char, std::any>{
                                     ATMA::NetworkMessageValueType(ATMA::NetworkMessageValueEnum::UNSIGNEDINT),
                                     m_playerChoices[1].second
                                 }
                            },
                        }
                    };
                    ATMA::Props right{
                        {
                            {
                                "you",
                                std::pair<unsigned char, std::any>{
                                    ATMA::NetworkMessageValueType(ATMA::NetworkMessageValueEnum::UNSIGNEDINT),
                                    m_playerChoices[1].second
                                }
                            },
                            {
                                 "them",
                                 std::pair<unsigned char, std::any>{
                                     ATMA::NetworkMessageValueType(ATMA::NetworkMessageValueEnum::UNSIGNEDINT),
                                     m_playerChoices[0].second
                                 }
                            },
                        }
                    };
                    switch(compare(m_playerChoices[0].second, m_playerChoices[1].second))
                    {
                    case -1:
                        {
                            ATMA::NetworkMessage nm{GameNetMessageType(GameNetMessageEnum::PLAYER_LOSE), left};
                            ctx.netManager.sendMessage(nm, m_playerChoices[0].first);
                            nm = ATMA::NetworkMessage{GameNetMessageType(GameNetMessageEnum::PLAYER_WIN), right};
                            ctx.netManager.sendMessage(nm, m_playerChoices[1].first);
                        }
                        break;
                    case 0:
                        {
                            ATMA::NetworkMessage nm{GameNetMessageType(GameNetMessageEnum::PLAYER_TIED), left};
                            ctx.netManager.sendMessage(nm, m_playerChoices[0].first);
                            nm = ATMA::NetworkMessage{GameNetMessageType(GameNetMessageEnum::PLAYER_TIED), right};
                            ctx.netManager.sendMessage(nm, m_playerChoices[1].first);
                        }
                        break;
                    case 1:
                        {
                            ATMA::NetworkMessage nm{GameNetMessageType(GameNetMessageEnum::PLAYER_WIN), left};
                            ctx.netManager.sendMessage(nm, m_playerChoices[0].first);
                            nm = ATMA::NetworkMessage{GameNetMessageType(GameNetMessageEnum::PLAYER_LOSE), right};
                            ctx.netManager.sendMessage(nm, m_playerChoices[1].first);
                        }
                        break;
                    case 2:
                        break;
                    }
                    m_playerChoices.clear();
                }
            }
            break;
        default:
            ATMA_ENGINE_INFO("skipped network message type: {}", msgType);
            break;
        }
    }

    /**
     * gets state id
     * @returns state id
     */
    virtual unsigned int getId() const override
    {
        return GameStateType(GameStateEnum::SERVER);
    }

    /**
     * passes window events to be handled by the state
     * @param l_winEvent the event generated by the window
     * @returns whether or not the event was handled
     */
    virtual void handleInput(const ATMA::WindowEvent &l_winEvent) {}
private:
    short compare(const unsigned int &l_left, const unsigned int &l_right)
    {
        switch(l_left)
        {
        case 0: // rock
            switch(l_right)
            {
            case 0: // rock vs. rock
                return 0;
            case 1: // rock vs. paper
                return -1;
            case 2: // rock vs. scissors
                return 1;
            }
            break;
        case 1: // paper
            switch(l_right)
            {
            case 0: // paper vs. rock
                return 1;
            case 1: // paper vs. paper
                return 0;
            case 2: // paper vs. scissors
                return -1;
            }
            break;
        case 2: // scissors
            switch(l_right)
            {
            case 0: // scissors vs. rock
                return -1;
            case 1: // scissors vs. paper
                return 1;
            case 2: // scissors vs. scissors
                return 0;
            }
            break;
        }
        return 2;
    }

    static const int MAX_PORTS = 2;
    std::vector<std::optional<unsigned int>> m_ports{};
    std::vector<std::pair<std::optional<unsigned int>, unsigned int>> m_playerChoices{};
};