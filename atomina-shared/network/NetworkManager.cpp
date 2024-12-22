#include "pch.hpp"
#include "NetworkManager.hpp"

namespace ATMA
{

    void NetworkConnection::run()
    {

        ATMA_ENGINE_INFO(
            "Starting connection thread for id {} with handle {}",
            m_id.value_or(std::numeric_limits<unsigned int>::max()),
            m_conn
        );
        size_t recvBytes;
        size_t totalBytes;
        unsigned char buf[NETWORKMESSAGEBUFFERSIZE];
        std::span<unsigned char> bufSpan{buf};
        std::vector<unsigned char> wholeMessage{};
        unsigned short messageSize;
        do
        {
            if(!m_conn->receiveBytes(bufSpan, ATMA::NETWORKMESSAGEBUFFERSIZE, recvBytes))
                continue;
            totalBytes = recvBytes;
            for(int i = 0; i < recvBytes; i++)
            {
                wholeMessage.emplace_back(bufSpan[i]);
            }
            std::copy(
                bufSpan.begin(),
                bufSpan.begin() + sizeof(unsigned short),
                reinterpret_cast<unsigned char *>(&messageSize)
            );
            while(totalBytes < messageSize)
            {
                m_conn->receiveBytes(bufSpan, ATMA::NETWORKMESSAGEBUFFERSIZE, recvBytes);
                totalBytes += recvBytes;
                for(int i = 0; i < recvBytes; i++)
                {
                    wholeMessage.emplace_back(bufSpan[i]);
                }
            }
            ATMA_ENGINE_INFO("Got Network message of {} bytes", totalBytes);
            NetworkMessage msg = NetworkSerde::deserialize(wholeMessage);
            NetworkMessageListener::dispatch(std::nullopt, msg, m_subscribers->at(msg.m_type));
        } while(recvBytes == 0 && *m_connected);
        if(m_id.has_value())
        {
            m_conn->closeSocket();
        }
    
        ATMA_ENGINE_INFO(
            "Terminating connection thread for id {}",
            m_id.value_or(std::numeric_limits<unsigned int>::max())
        );
        
    }

    void NetworkListener::run()
    {
        ATMA_ENGINE_INFO("Starting listening thread");
        while(*m_listening)
        {
            if(auto sock = m_listener->acceptConnection(); sock != nullptr)
            {
                m_idMutex->lock();
                const ConnId id = *m_lastId;
                ATMA_ENGINE_INFO("Accepting connection with id {}", id);
                (*m_lastId)++;
                m_idMutex->unlock();
                sock->setBlocking(false);
                std::optional<const ConnId> idOpt{id};
                std::shared_ptr<bool> connected = std::make_shared<bool>(true);
                std::shared_ptr<NetworkConnection> conn = std::make_shared<NetworkConnection>(
                    idOpt, 
                    sock, 
                    connected,
                    m_subscribers
                );
                (*m_connections)[id] = std::make_shared<Conn>(std::make_pair(connected, conn));
                NetworkMessage msg{NetworkMessageType(NetworkMessageEnum::CONNECTION_STARTED)};
                auto itr = m_subscribers->find(msg.m_type);
                if(itr != m_subscribers->end())
                    NetworkMessageListener::dispatch(idOpt, msg, itr->second);
                sock = nullptr;
            }

        }
        ATMA_ENGINE_INFO("Terminating listening thread");
    }

    NetworkManager::NetworkManager() {}

    NetworkManager::~NetworkManager()
    {
        ATMA_ENGINE_INFO("Shutting down Network Manager");
        *m_listening = false;
        *m_connected = false;
        if(m_listener != nullptr)
        {
            m_listener = nullptr;
        }
        if(m_listenerSocket != nullptr)
        {
            m_listenerSocket->stopListening();
        }

        if(m_conn != nullptr)
        {
            m_conn = nullptr;
        }
        if(m_connSocket != nullptr)
        {
            m_connSocket->closeSocket();
        }
        for (auto& c : *m_connections)
        {
            *(c.second->first) = false;
        }
        m_connections->clear();
    }

    void NetworkManager::startHosting(const unsigned int &l_port)
    {
        m_listenerSocket = SocketListener::makeSocketListener(l_port);
        if(*m_listening)
        {
            ATMA_ENGINE_WARN("Already listening");
            return;
        }
        *m_listening = true;
        m_listenerSocket->startListening();
        ATMA_ENGINE_INFO("Creating Network Listener");
        m_listener = std::make_unique<NetworkListener>(
            m_listenerSocket,
            m_listening,
            m_connIdMutex,
            m_connections,
            m_lastConnId,
            m_subscribers
        );
    }

    void NetworkManager::broadcastMessage(const NetworkMessage &l_msg)
    {
        std::vector<unsigned char> msg = NetworkSerde::serialize(l_msg);
        for(auto &conn: *m_connections)
        {
            conn.second->second->send(l_msg);
        }
    }

    void NetworkManager::stopHosting()
    {
        ATMA_ENGINE_INFO("notifying listening thread to stop");
        *m_listening = false;
        m_listenerSocket->stopListening();
        m_listenerSocket = nullptr;
    }

    void NetworkManager::startConnection(const URL &l_url, const unsigned short &l_port)
    {
        if(*m_connected)
        {
            ATMA_ENGINE_WARN("Already connected");
            return;
        }
        m_connSocket = Socket::makeSocket();
        m_connSocket->connectSocket(l_url, l_port);
        m_connSocket->setBlocking(false);
        *m_connected = true;
        ATMA_ENGINE_INFO("Creating Network Connection");
        m_conn = std::make_unique<NetworkConnection>(std::nullopt, m_connSocket, m_connected, m_subscribers);
    }

    void NetworkManager::sendMessage(
        const NetworkMessage &l_msg,
        const std::optional<const ConnId> &l_id
    )
    {
        std::vector<unsigned char> msg = NetworkSerde::serialize(l_msg);
        if (l_id.has_value())
        {
            (*m_connections)[l_id.value()]->second->send(l_msg);
        }
        else
        {
            m_connSocket->sendBytes(msg, msg.size());
        }


    }

    void NetworkManager::stopConnection(const std::optional<const ConnId> &l_id)
    {
        ATMA_ENGINE_INFO(
            "notifying connection thread to stop {}",
            l_id.value_or(std::numeric_limits<const ConnId>::max())
        );
        if(l_id.has_value())
        {
            if (auto c = m_connections->find(l_id.value()); c != m_connections->end())
            {
                *(c->second->first) = false;
                m_connections->erase(l_id.value());
            }
        }
        else
        {
            *m_connected = false;
            m_connSocket->closeSocket();
            m_connSocket = nullptr;
        }
    }

    void NetworkManager::addMessageListener(
        const unsigned int &l_type,
        std::shared_ptr<NetworkMessageListener> l_listener
    )
    {
        auto itr = m_subscribers->find(l_type);
        if(itr == m_subscribers->end())
        {
            std::vector<std::shared_ptr<NetworkMessageListener>> newVec{l_listener};
            (*m_subscribers)[l_type] = newVec;
            ATMA_ENGINE_INFO(
                "Network Event Listener for Network Event Type: {0:d} has been added", l_type
            );
        }
        else
        {
            (*m_subscribers)[l_type].emplace_back(l_listener);
            ATMA_ENGINE_INFO(
                "Network Event Listener for Network Event Type: {0:d} has been added", l_type
            );
        }
    }

    void NetworkManager::purgeListeners()
    {
        m_subscribers->clear();
    }

}