#pragma once
#include <atomina.hpp>
#include "../GameEnums.hpp"
#include "../OAS/AttrTimer.hpp"

struct AttackOptionButton
{
    std::shared_ptr<ATMA::AttrRenderable> m_button{};
    unsigned int m_buttonId;
    std::shared_ptr<ATMA::AttrRenderable> m_icon{};
    unsigned int m_iconId;
    std::shared_ptr<ATMA::AttrText> m_text{};
    unsigned int m_textId;
};

struct PlayerScore
{
    std::shared_ptr<ATMA::AttrText> m_scoreText{};
    unsigned int m_scoreTextId;
    std::shared_ptr<ATMA::AttrText> m_scoreName{};
    unsigned int m_scoreNameId;
};

struct Message
{
    std::shared_ptr<ATMA::AttrText> m_messageText{};
    unsigned int m_messageId;
};

struct ResultIcon
{
    std::shared_ptr<ATMA::AttrRenderable> m_icon{};
    unsigned int m_iconId;
};

struct Timer
{
    std::shared_ptr<AttrTimer> m_timer{};
    unsigned int m_timerId;
};

class PlayState: public ATMA::BaseState, public ATMA::ObjectEventListener
{
public:
    ATMA::ATMAContext &ctx = ATMA::ATMAContext::getContext();

    PlayState(
        std::shared_ptr<ATMA::AppWindow> l_win,
        const unsigned int &l_vertID,
        const unsigned int &l_fragID,
        const unsigned int &l_fontID
    ):
        BaseState()
    {
        m_win = l_win;
        auto vertShader = ctx.loadResource<ATMA::GLShader>(l_vertID);
        vertShader->compile(ATMA::ShaderType::Vertex);
        auto fragShader = ctx.loadResource<ATMA::GLShader>(l_fragID);
        fragShader->compile(ATMA::ShaderType::Fragment);
        m_defaultProg = ATMA::GLProgram::makeProgram();
        m_defaultProg->attachShader(vertShader);
        m_defaultProg->attachShader(fragShader);
        m_defaultProg->link();
        auto selectedTextID = ctx.registerResource("selected", 0u, "res/selected.png");
        auto unselectedTextID = ctx.registerResource("unselected", 0u, "res/unselected.png");
        auto selectedRockTextID = ctx.registerResource("selected", 0u, "res/selectedRock.png");
        auto unselectedRockTextID = ctx.registerResource("unselected", 0u, "res/unselectedRock.png");
        auto selectedPaperTextID = ctx.registerResource("selected", 0u, "res/selectedPaper.png");
        auto unselectedPaperTextID = ctx.registerResource("unselected", 0u, "res/unselectedPaper.png");
        auto selectedScissorsTextID = ctx.registerResource("selected", 0u, "res/selectedScissors.png");
        auto unselectedScissorsTextID = ctx.registerResource("unselected", 0u, "res/unselectedScissors.png");
        m_font = ctx.loadResource<ATMA::GLTexture>(l_fontID);
        m_selectedTexture = ctx.loadResource<ATMA::GLTexture>(selectedTextID);
        m_unselectedTexture = ctx.loadResource<ATMA::GLTexture>(unselectedTextID);
        m_selectedRockTexture = ctx.loadResource<ATMA::GLTexture>(selectedRockTextID);
        m_unselectedRockTexture = ctx.loadResource<ATMA::GLTexture>(unselectedRockTextID);
        m_selectedPaperTexture = ctx.loadResource<ATMA::GLTexture>(selectedPaperTextID);
        m_unselectedPaperTexture = ctx.loadResource<ATMA::GLTexture>(unselectedPaperTextID);
        m_selectedScissorsTexture = ctx.loadResource<ATMA::GLTexture>(selectedScissorsTextID);
        m_unselectedScissorsTexture = ctx.loadResource<ATMA::GLTexture>(unselectedScissorsTextID);
        for(int i = 0; i < 3; ++i)
        {
            m_buttons[i].m_buttonId = ctx.createObject();
            m_buttons[i].m_iconId = ctx.createObject();
            m_buttons[i].m_textId = ctx.createObject();
        }
        for(int i = 0; i < 2; ++i)
        {
            m_scoreText[i].m_scoreNameId = ctx.createObject();
            m_scoreText[i].m_scoreTextId = ctx.createObject();
            m_results[i].m_iconId = ctx.createObject();
        }
        m_message.m_messageId = ctx.createObject();
        m_resultTimer.m_timerId = ctx.createObject();
    }

    virtual ~PlayState() {}

    /**
     * stub implementation of activate function
     */
    virtual void activate() override
    {
        m_active = true;
        m_selected = 0;
        m_substate = 0;
        // ctx.m_renderCtx->setFont(m_font);

        addButtons();
        for(int i = 0; i < 2; ++i)
        {
            ctx.addAttribute(m_scoreText[i].m_scoreNameId, ATMA::AttributeType(ATMA::Attribute::Text));
            ctx.addAttribute(m_scoreText[i].m_scoreTextId, ATMA::AttributeType(ATMA::Attribute::Text));
            m_scoreText[i].m_scoreName = ctx.getAttribute<ATMA::AttrText>(
                m_scoreText[i].m_scoreNameId, ATMA::AttributeType(ATMA::Attribute::Text)
            );
            m_scoreText[i].m_scoreText = ctx.getAttribute<ATMA::AttrText>(
                m_scoreText[i].m_scoreTextId, ATMA::AttributeType(ATMA::Attribute::Text)
            );
            m_scoreText[i].m_scoreName->m_self->m_prog = m_defaultProg;
            m_scoreText[i].m_scoreName->m_self->m_texture = m_font;
            m_scoreText[i].m_scoreName->m_self->m_stackPos = 2;
            m_scoreText[i].m_scoreText->m_self->m_prog = m_defaultProg;
            m_scoreText[i].m_scoreText->m_self->m_texture = m_font;
            m_scoreText[i].m_scoreText->m_self->m_stackPos = 2;
            m_scoreText[i].m_scoreText->m_self->m_text = std::to_string(m_score[i]);
        }
        m_scoreText[0].m_scoreName->m_self->m_text = "You";
        m_scoreText[0].m_scoreName->m_self->m_size = ATMA::Vec2<float>{7.f, 10.f};
        m_scoreText[0].m_scoreName->m_self->m_pos = ATMA::Vec2<float>{-175.f, 200.f};
        m_scoreText[0].m_scoreText->m_self->m_size = ATMA::Vec2<float>{7.f, 10.f};
        m_scoreText[0].m_scoreText->m_self->m_pos = ATMA::Vec2<float>{-175.f, 180.f};
        m_scoreText[1].m_scoreName->m_self->m_text = "Other Player";
        m_scoreText[1].m_scoreName->m_self->m_size = ATMA::Vec2<float>{7.f, 10.f};
        m_scoreText[1].m_scoreName->m_self->m_pos = ATMA::Vec2<float>{175.f, 200.f};
        m_scoreText[1].m_scoreText->m_self->m_size = ATMA::Vec2<float>{7.f, 10.f};
        m_scoreText[1].m_scoreText->m_self->m_pos = ATMA::Vec2<float>{175.f, 180.f};

        ctx.onUpdate([&](const long long &l_dt) {});
    }

    /**
     * stub implementation of deactivate function
     */
    virtual void deactivate() override
    {
        m_active = false;
        removeButtons();
        for(int i = 0; i < 2; ++i)
        {
            ctx.removeAttribute(m_scoreText[i].m_scoreNameId, ATMA::AttributeType(ATMA::Attribute::Text));
            ctx.removeAttribute(m_scoreText[i].m_scoreTextId, ATMA::AttributeType(ATMA::Attribute::Text));
            if(ctx.hasAttribute(m_results[i].m_iconId, ATMA::AttributeType(ATMA::Attribute::Render)))
                ctx.removeAttribute(m_results[i].m_iconId, ATMA::AttributeType(ATMA::Attribute::Render));
        }
        if(ctx.hasAttribute(m_message.m_messageId, ATMA::AttributeType(ATMA::Attribute::Text)))
            ctx.removeAttribute(m_message.m_messageId, ATMA::AttributeType(ATMA::Attribute::Text));
        if(ctx.hasAttribute(m_resultTimer.m_timerId, GameAttributeType(GameAttributeEnum::TIMER)))
            ctx.removeAttribute(m_resultTimer.m_timerId, GameAttributeType(GameAttributeEnum::TIMER));
    }

    virtual void notify(const ATMA::ObjectEventContext &l_e) override
    {
        switch(l_e.m_objectEventType)
        {
        case static_cast<unsigned int>(ATMA::ObjectEvent::Network):
            {
                ATMA_ENGINE_TRACE("handling event in server state");
                unsigned int msgType = l_e.m_properties.getAs<unsigned int>("msgType");
                ATMA_ENGINE_TRACE("getting conn id from object event message");
                std::optional<unsigned int> connId = l_e.m_properties.getAs<std::optional<unsigned int>>("connId");
                ATMA_ENGINE_TRACE("got conn id from object message");
                switch(msgType)
                {
                case static_cast<unsigned int>(GameNetMessageEnum::PLAYER_WIN):
                    [[fallthrough]];
                case static_cast<unsigned int>(GameNetMessageEnum::PLAYER_TIED):
                    [[fallthrough]];
                case static_cast<unsigned int>(GameNetMessageEnum::PLAYER_LOSE):
                    {
                        m_substate = 2;
                        for(int i = 0; i < 2; ++i)
                        {
                            ctx.addAttribute(m_results[i].m_iconId, ATMA::AttributeType(ATMA::Attribute::Render));
                            m_results[i].m_icon = ctx.getAttribute<ATMA::AttrRenderable>(
                                m_results[i].m_iconId, ATMA::AttributeType(ATMA::Attribute::Render)
                            );
                            m_results[i].m_icon->m_self->m_prog = m_defaultProg;
                            m_results[i].m_icon->m_self->m_size = ATMA::Vec2<float>{50.f, 90.f};
                            m_results[i].m_icon->m_self->m_stackPos = 0;
                        }
                        m_results[0].m_icon->m_self->m_pos = ATMA::Vec2<float>{-200.f, 0.f};
                        m_results[0].m_icon->m_self->m_texture =
                            mapTexture(l_e.m_properties.getAs<unsigned int>("you"));
                        m_results[1].m_icon->m_self->m_pos = ATMA::Vec2<float>{200.f, 0.f};
                        m_results[1].m_icon->m_self->m_texture =
                            mapTexture(l_e.m_properties.getAs<unsigned int>("them"));
                        ctx.addAttribute(m_resultTimer.m_timerId, GameAttributeType(GameAttributeEnum::TIMER));
                        m_resultTimer.m_timer = ctx.getAttribute<AttrTimer>(
                            m_resultTimer.m_timerId, GameAttributeType(GameAttributeEnum::TIMER)
                        );
                        m_resultTimer.m_timer->m_amount = 2000000000LL;
                        m_resultTimer.m_timer->m_clock.start();
                        break;
                    }
                }
                switch(msgType)
                {
                case static_cast<unsigned int>(GameNetMessageEnum::PLAYER_WIN):
                    {
                        m_message.m_messageText->m_self->m_text = "You Win";
                        m_score[0]++;
                        m_scoreText[0].m_scoreText->m_self->m_text = std::to_string(m_score[0]);
                    }
                    break;
                case static_cast<unsigned int>(GameNetMessageEnum::PLAYER_TIED):
                    {
                        m_message.m_messageText->m_self->m_text = "You Tied";
                    }
                    break;
                case static_cast<unsigned int>(GameNetMessageEnum::PLAYER_LOSE):
                    {
                        m_message.m_messageText->m_self->m_text = "You Lose";
                        m_score[1]++;
                        m_scoreText[1].m_scoreText->m_self->m_text = std::to_string(m_score[1]);
                    }
                    break;
                }
            }
            break;
        case static_cast<unsigned int>(GameEventEnum::TIMER_COMPLETE):
            {
                m_substate = 0;
                for(int i = 0; i < 2; ++i)
                {
                    if(ctx.hasAttribute(m_results[i].m_iconId, ATMA::AttributeType(ATMA::Attribute::Render)))
                        ctx.removeAttribute(m_results[i].m_iconId, ATMA::AttributeType(ATMA::Attribute::Render));
                }
                if(ctx.hasAttribute(m_message.m_messageId, ATMA::AttributeType(ATMA::Attribute::Text)))
                    ctx.removeAttribute(m_message.m_messageId, ATMA::AttributeType(ATMA::Attribute::Text));
                if(ctx.hasAttribute(m_resultTimer.m_timerId, GameAttributeType(GameAttributeEnum::TIMER)))
                    ctx.removeAttribute(m_resultTimer.m_timerId, GameAttributeType(GameAttributeEnum::TIMER));
                m_selected = 0;
                addButtons();
            }
            break;
        }
    }

    /**
     * gets state id
     * @returns state id
     */
    virtual unsigned int getId() const override
    {
        return GameStateType(GameStateEnum::PLAYSTATE);
    }

    /**
     * passes window events to be handled by the state
     * @param l_winEvent the event generated by the window
     * @returns whether or not the event was handled
     */
    virtual void handleInput(const ATMA::WindowEvent &l_winEvent)
    {
        if(!m_active)
            return;
        switch(l_winEvent.m_type)
        {
        case ATMA::WindowEventEnum::KeyDowned:
            if(m_substate != 0)
                break;
            {
                int keyindex = l_winEvent.getProp<int>("keycode"s);
                ATMA::KeyEnum keycode = ATMA::KeyEnum(keyindex);
                ATMA_ENGINE_INFO("key pressed with code {}", keyindex);
                switch(keycode)
                {
                case ATMA::KeyEnum::LEFT:
                    m_buttons[m_selected].m_button->m_self->m_texture = m_unselectedTexture;
                    if(m_selected == 0)
                    {
                        m_selected = 2;
                    }
                    else
                    {
                        m_selected--;
                    }
                    switch(m_selected)
                    {
                    case 0:
                        m_buttons[m_selected].m_icon->m_self->m_texture = m_selectedRockTexture;
                        m_buttons[1].m_icon->m_self->m_texture = m_unselectedPaperTexture;
                        break;
                    case 1:
                        m_buttons[m_selected].m_icon->m_self->m_texture = m_selectedPaperTexture;
                        m_buttons[2].m_icon->m_self->m_texture = m_unselectedScissorsTexture;
                        break;
                    case 2:
                        m_buttons[m_selected].m_icon->m_self->m_texture = m_selectedScissorsTexture;
                        m_buttons[0].m_icon->m_self->m_texture = m_unselectedRockTexture;
                        break;
                    }
                    m_buttons[m_selected].m_button->m_self->m_texture = m_selectedTexture;
                    break;
                case ATMA::KeyEnum::RIGHT:
                    m_buttons[m_selected].m_button->m_self->m_texture = m_unselectedTexture;
                    if(m_selected == 2)
                    {
                        m_selected = 0;
                    }
                    else
                    {
                        m_selected++;
                    }
                    switch(m_selected)
                    {
                    case 0:
                        m_buttons[m_selected].m_icon->m_self->m_texture = m_selectedRockTexture;
                        m_buttons[2].m_icon->m_self->m_texture = m_unselectedScissorsTexture;
                        break;
                    case 1:
                        m_buttons[m_selected].m_icon->m_self->m_texture = m_selectedPaperTexture;
                        m_buttons[0].m_icon->m_self->m_texture = m_unselectedRockTexture;
                        break;
                    case 2:
                        m_buttons[m_selected].m_icon->m_self->m_texture = m_selectedScissorsTexture;
                        m_buttons[1].m_icon->m_self->m_texture = m_unselectedPaperTexture;
                        break;
                    }
                    m_buttons[m_selected].m_button->m_self->m_texture = m_selectedTexture;
                    break;
                case ATMA::KeyEnum::RETURN:
                    {
                        removeButtons();
                        m_substate = 1;
                        ATMA::Props p{
                            {{"choice",
                              std::pair<unsigned char, std::any>{
                                  ATMA::NetworkMessageValueType(ATMA::NetworkMessageValueEnum::UNSIGNEDINT), m_selected
                              }}}
                        };
                        ATMA::NetworkMessage nm{GameNetMessageType(GameNetMessageEnum::PLAYER_CHOICE), p};
                        ctx.netManager.sendMessage(nm);
                        ctx.addAttribute(m_message.m_messageId, ATMA::AttributeType(ATMA::Attribute::Text));
                        m_message.m_messageText = ctx.getAttribute<ATMA::AttrText>(
                            m_message.m_messageId, ATMA::AttributeType(ATMA::Attribute::Text)
                        );
                        m_message.m_messageText->m_self->m_prog = m_defaultProg;
                        m_message.m_messageText->m_self->m_texture = m_font;
                        m_message.m_messageText->m_self->m_stackPos = 1;
                        m_message.m_messageText->m_self->m_text = "Waiting for Opponent";
                        m_message.m_messageText->m_self->m_size = ATMA::Vec2<float>{7.f, 10.f};
                        m_message.m_messageText->m_self->m_pos = ATMA::Vec2<float>{-30.f, 0.f};
                    }

                    break;
                }

                break;
            }
        case ATMA::WindowEventEnum::Resized:
            break;
        case ATMA::WindowEventEnum::Closed:
            l_winEvent.m_win->notifyClose();
            break;
        }
        return;
    }
private:
    void addButtons()
    {
        for(int i = 0; i < 3; i++)
        {
            ctx.addAttribute(m_buttons[i].m_buttonId, ATMA::AttributeType(ATMA::Attribute::Render));
            ctx.addAttribute(m_buttons[i].m_iconId, ATMA::AttributeType(ATMA::Attribute::Render));
            ctx.addAttribute(m_buttons[i].m_textId, ATMA::AttributeType(ATMA::Attribute::Text));
            m_buttons[i].m_button = ctx.getAttribute<ATMA::AttrRenderable>(
                m_buttons[i].m_buttonId, ATMA::AttributeType(ATMA::Attribute::Render)
            );
            m_buttons[i].m_icon = ctx.getAttribute<ATMA::AttrRenderable>(
                m_buttons[i].m_iconId, ATMA::AttributeType(ATMA::Attribute::Render)
            );
            m_buttons[i].m_text =
                ctx.getAttribute<ATMA::AttrText>(m_buttons[i].m_textId, ATMA::AttributeType(ATMA::Attribute::Text));
            m_buttons[i].m_button->m_self->m_prog = m_defaultProg;
            m_buttons[i].m_button->m_self->m_texture = m_unselectedTexture;
            m_buttons[i].m_button->m_self->m_size = ATMA::Vec2<float>{50.f, 90.f};
            m_buttons[i].m_button->m_self->m_stackPos = 0;
            m_buttons[i].m_icon->m_self->m_prog = m_defaultProg;
            m_buttons[i].m_icon->m_self->m_size = ATMA::Vec2<float>{40.f, 40.f};
            m_buttons[i].m_icon->m_self->m_stackPos = 1;
            m_buttons[i].m_text->m_self->m_prog = m_defaultProg;
            m_buttons[i].m_text->m_self->m_texture = m_font;
            m_buttons[i].m_text->m_self->m_stackPos = 2;
        }
        m_buttons[0].m_text->m_self->m_text = "Rock";
        m_buttons[0].m_text->m_self->m_size = ATMA::Vec2<float>{7.f, 10.f};
        m_buttons[0].m_text->m_self->m_pos = ATMA::Vec2<float>{-155.f, -65.f};
        m_buttons[0].m_icon->m_self->m_texture = m_selectedRockTexture;
        m_buttons[0].m_icon->m_self->m_pos = ATMA::Vec2<float>{-135.f, 0.f};
        m_buttons[0].m_button->m_self->m_pos = ATMA::Vec2<float>{-135.f, 0.f};
        m_buttons[0].m_button->m_self->m_texture = m_selectedTexture;

        m_buttons[1].m_text->m_self->m_text = "Paper";
        m_buttons[1].m_text->m_self->m_size = ATMA::Vec2<float>{7.f, 10.f};
        m_buttons[1].m_text->m_self->m_pos = ATMA::Vec2<float>{-25.f, -65.f};
        m_buttons[1].m_icon->m_self->m_texture = m_unselectedPaperTexture;
        m_buttons[1].m_icon->m_self->m_pos = ATMA::Vec2<float>{0.f, 0.f};
        m_buttons[1].m_button->m_self->m_pos = ATMA::Vec2<float>{0.f, 0.f};

        m_buttons[2].m_text->m_self->m_text = "Scissors";
        m_buttons[2].m_text->m_self->m_size = ATMA::Vec2<float>{7.f, 10.f};
        m_buttons[2].m_text->m_self->m_pos = ATMA::Vec2<float>{90.f, -65.f};
        m_buttons[2].m_icon->m_self->m_texture = m_unselectedScissorsTexture;
        m_buttons[2].m_icon->m_self->m_pos = ATMA::Vec2<float>{135.f, 0.f};
        m_buttons[2].m_button->m_self->m_pos = ATMA::Vec2<float>{135.f, 0.f};
    }

    void removeButtons()
    {
        for(int i = 0; i < 3; i++)
        {
            ctx.removeAttribute(m_buttons[i].m_buttonId, ATMA::AttributeType(ATMA::Attribute::Render));
            ctx.removeAttribute(m_buttons[i].m_iconId, ATMA::AttributeType(ATMA::Attribute::Render));
            ctx.removeAttribute(m_buttons[i].m_textId, ATMA::AttributeType(ATMA::Attribute::Text));
        }
    }

    std::shared_ptr<ATMA::GLTexture> mapTexture(const unsigned int &l_type)
    {
        switch(l_type)
        {
        case 0:
            return m_selectedRockTexture;
        case 1:
            return m_selectedPaperTexture;
        case 2:
            return m_selectedScissorsTexture;
        }
    }

    AttackOptionButton m_buttons[3]{};
    PlayerScore m_scoreText[2]{};
    Message m_message;
    ResultIcon m_results[2]{};
    Timer m_resultTimer;
    unsigned int m_selected;
    unsigned int m_substate;
    unsigned int m_score[2]{0, 0};
    std::shared_ptr<ATMA::GLTexture> m_selectedTexture;
    std::shared_ptr<ATMA::GLTexture> m_unselectedTexture;
    std::shared_ptr<ATMA::GLTexture> m_selectedRockTexture;
    std::shared_ptr<ATMA::GLTexture> m_unselectedRockTexture;
    std::shared_ptr<ATMA::GLTexture> m_selectedPaperTexture;
    std::shared_ptr<ATMA::GLTexture> m_unselectedPaperTexture;
    std::shared_ptr<ATMA::GLTexture> m_selectedScissorsTexture;
    std::shared_ptr<ATMA::GLTexture> m_unselectedScissorsTexture;
    std::shared_ptr<ATMA::GLTexture> m_font;
    std::shared_ptr<ATMA::GLProgram> m_defaultProg;
    std::shared_ptr<ATMA::AppWindow> m_win;
};