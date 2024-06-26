#pragma once
#include <atomina.hpp>
#include "GameStateType.hpp"
#include "GameEventType.hpp"

class PlayState: public ATMA::BaseState, public ATMA::ObjectEventListener
{
public:
    ATMA::ATMAContext &ctx = ATMA::ATMAContext::getContext();

    PlayState(): ATMA::BaseState()
    {
        auto playerTextID = ctx.registerResource("shaggy player", 0u, "res/shaggysheet.png");
        auto wallTextID = ctx.registerResource("wall", 0u, "res/wall.png");
        auto fontID = ctx.registerResource("font", 1u, "res/defaultFont.png");
        m_font = ctx.loadResource<ATMA::Font>(fontID);
        m_playerTexture = ctx.loadResource<ATMA::Texture>(playerTextID);
        m_wallTexture = ctx.loadResource<ATMA::Texture>(wallTextID);
        m_playerID = ctx.createObject();
        m_promptID = ctx.createObject();
        m_gameOverID = ctx.createObject();
        m_highScoreID = ctx.createObject();
        m_firstPipe = m_highScoreID;
    }

    virtual ~PlayState() {}

    /**
     * stub implementation of activate function
     */
    virtual void activate() override
    {
        m_active = true;
        m_started = false;
        m_gameOver = false;
        ctx.m_renderCtx->setFont(m_font);
        ctx.addAttribute(m_playerID, ATMA::AttributeType(ATMA::Attribute::Render));
        ctx.addAttribute(m_playerID, ATMA::AttributeType(ATMA::Attribute::Shape));
        ctx.addAttribute(m_playerID, ATMA::AttributeType(ATMA::Attribute::Velocity));
        ctx.addAttribute(m_playerID, ATMA::AttributeType(ATMA::Attribute::Collidable));
        ctx.addAttribute(m_promptID, ATMA::AttributeType(ATMA::Attribute::Render));
        auto playerRender = ctx.getAttribute<ATMA::AttrRenderable>(
            m_playerID, ATMA::AttributeType(ATMA::Attribute::Render)
        );
        playerRender->m_element = m_playerTexture->m_self;
        playerRender->m_srcRegion = ATMA::Vec2<float>{0.5f, 1.f};
        playerRender->m_region = ATMA::Vec2<float>{0.1f, 0.2f};
        playerRender->m_srcPos = ATMA::Vec2<float>{0.5f, 0.f};
        playerRender->m_screenPos = ATMA::Vec2<float>{0.f, 0.f};
        playerRender->m_stackPos = 0;
        auto playerCollide = ctx.getAttribute<ATMA::AttrCollidable>(m_playerID, ATMA::AttributeType(ATMA::Attribute::Collidable));
        playerCollide->m_collider.a = ATMA::Vec2<float>{0,0};
        playerCollide->m_collider.b = ATMA::Vec2<float>{0,0.07f};
        playerCollide->m_collider.r = 0.03f;
        auto promptRender = ctx.getAttribute<ATMA::AttrRenderable>(
            m_promptID, ATMA::AttributeType(ATMA::Attribute::Render)
        );
        promptRender->m_element = "Press Space";
        promptRender->m_region = ATMA::Vec2<float>{0.04f, 0.1f};
        promptRender->m_screenPos = ATMA::Vec2<float>{-0.4f, 0.22f};
        promptRender->m_stackPos = 1;
        m_highScore = 0;
    }

    /**
     * stub implementation of deactive function
     */
    virtual void deactivate() override
    {
        m_active = false;
        ctx.removeAttribute(m_playerID, ATMA::AttributeType(ATMA::Attribute::Render));
        ctx.removeAttribute(m_playerID, ATMA::AttributeType(ATMA::Attribute::Shape));
        ctx.removeAttribute(m_playerID, ATMA::AttributeType(ATMA::Attribute::Velocity));
        if(ctx.hasAttribute(m_playerID, ATMA::AttributeType(ATMA::Attribute::Controllable)))
            ctx.removeAttribute(m_playerID, ATMA::AttributeType(ATMA::Attribute::Controllable));
        if(ctx.hasAttribute(m_promptID, ATMA::AttributeType(ATMA::Attribute::Render)))
            ctx.removeAttribute(m_promptID, ATMA::AttributeType(ATMA::Attribute::Render));
        if(ctx.hasAttribute(m_gameOverID, ATMA::AttributeType(ATMA::Attribute::Render)))
            ctx.removeAttribute(m_gameOverID, ATMA::AttributeType(ATMA::Attribute::Render));
        if(ctx.hasAttribute(m_highScoreID, ATMA::AttributeType(ATMA::Attribute::Render)))
            ctx.removeAttribute(m_highScoreID, ATMA::AttributeType(ATMA::Attribute::Render));
        if(ctx.hasAttribute(m_highScoreID, ATMA::AttributeType(ATMA::Attribute::Collidable)))
            ctx.removeAttribute(m_highScoreID, ATMA::AttributeType(ATMA::Attribute::Collidable));
        for(auto &pipes: m_pipes)
        {
            ctx.removeAttribute(pipes.first, ATMA::AttributeType(ATMA::Attribute::Shape));
            ctx.removeAttribute(pipes.first, ATMA::AttributeType(ATMA::Attribute::Render));
            ctx.removeAttribute(pipes.first, ATMA::AttributeType(ATMA::Attribute::Velocity));
            ctx.removeAttribute(pipes.first, ATMA::AttributeType(ATMA::Attribute::Collidable));
            ctx.removeAttribute(pipes.second, ATMA::AttributeType(ATMA::Attribute::Shape));
            ctx.removeAttribute(pipes.second, ATMA::AttributeType(ATMA::Attribute::Render));
            ctx.removeAttribute(pipes.second, ATMA::AttributeType(ATMA::Attribute::Velocity));
            ctx.removeAttribute(pipes.second, ATMA::AttributeType(ATMA::Attribute::Collidable));
        }
        m_firstPipe = (m_pipes.end() - 1)->second;
        m_pipes.clear();
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
            {

                ATMA::KeyEnum keycode = ATMA::KeyEnum(l_winEvent.getProp<unsigned int>("keycode"s));
                switch(keycode)
                {
                case ATMA::KeyEnum::ESCAPE:
                    ctx.switchToState(GameStateType(GameStateEnum::MAINMENU));
                    break;
                case ATMA::KeyEnum::SPACE:
                    if(!l_winEvent.getProp<bool>("repeat"))
                    {
                        if(m_started && !m_gameOver)
                        {
                            ctx.dispatchObjectEvent(ATMA::ObjectEventContext{
                                GameEventType(GameEventEnum::FLAP), ATMA::Props{}});
                            ctx.onUpdate(
                                [&](const long long &l_dt)
                                {
                                    // pipe spawn logic
                                    m_lastSpawn += (l_dt >> 21);
                                    auto highScoreRender = ctx.getAttribute<ATMA::AttrRenderable>(
                                        m_highScoreID, ATMA::AttributeType(ATMA::Attribute::Render)
                                    );
                                    highScoreRender->m_element =
                                        "High Score: " + std::to_string(m_highScore);
                                    for(auto pipes = m_pipes.begin(); pipes < m_pipes.end();)
                                    {
                                        auto shape = ctx.getAttribute<ATMA::AttrShape>(
                                            pipes->first,
                                            ATMA::AttributeType(ATMA::Attribute::Shape)
                                        );
                                        auto renderTop = ctx.getAttribute<ATMA::AttrRenderable>(
                                            pipes->first,
                                            ATMA::AttributeType(ATMA::Attribute::Render)
                                        );
                                        auto renderBot = ctx.getAttribute<ATMA::AttrRenderable>(
                                            pipes->second,
                                            ATMA::AttributeType(ATMA::Attribute::Render)
                                        );
                                        auto collideTop = ctx.getAttribute<ATMA::AttrCollidable>(
                                            pipes->first,
                                            ATMA::AttributeType(ATMA::Attribute::Collidable)
                                        );
                                        auto collideBot = ctx.getAttribute<ATMA::AttrCollidable>(
                                            pipes->second,
                                            ATMA::AttributeType(ATMA::Attribute::Collidable)
                                        );
                                        renderTop->m_screenPos.x = shape->m_pos.x;
                                        renderBot->m_screenPos.x = shape->m_pos.x;
                                        collideTop->m_collider.setBase(ATMA::Vec2<float>{
                                            shape->m_pos.x, collideTop->m_collider.getBase().y});
                                        collideBot->m_collider.setBase(ATMA::Vec2<float>{
                                            shape->m_pos.x, collideBot->m_collider.getBase().y});
                                        if(renderTop->m_screenPos.x < 0.f
                                           && (pipes->first - m_firstPipe) / 2 - m_highScore == 0)
                                            m_highScore++;
                                        if(renderTop->m_screenPos.x < -1.f)
                                        {
                                            ctx.removeAttribute(
                                                pipes->first,
                                                ATMA::AttributeType(ATMA::Attribute::Shape)
                                            );
                                            ctx.removeAttribute(
                                                pipes->first,
                                                ATMA::AttributeType(ATMA::Attribute::Render)
                                            );
                                            ctx.removeAttribute(
                                                pipes->first,
                                                ATMA::AttributeType(ATMA::Attribute::Velocity)
                                            );
                                            ctx.removeAttribute(
                                                pipes->first,
                                                ATMA::AttributeType(ATMA::Attribute::Collidable)
                                            );
                                            ctx.removeAttribute(
                                                pipes->second,
                                                ATMA::AttributeType(ATMA::Attribute::Shape)
                                            );
                                            ctx.removeAttribute(
                                                pipes->second,
                                                ATMA::AttributeType(ATMA::Attribute::Render)
                                            );
                                            ctx.removeAttribute(
                                                pipes->second,
                                                ATMA::AttributeType(ATMA::Attribute::Velocity)
                                            );
                                            ctx.removeAttribute(
                                                pipes->second,
                                                ATMA::AttributeType(ATMA::Attribute::Collidable)
                                            );
                                            pipes = m_pipes.erase(pipes);
                                        }
                                        else
                                        {
                                            ++pipes;
                                        }
                                    }
                                    if(m_lastSpawn > (1000 - std::min(450u, m_highScore * 3)))
                                    {

                                        float middleOffset = m_floatRand(
                                            std::min(150u, m_highScore) / -400.f,
                                            std::min(150u, m_highScore) / 400.f
                                        );

                                        float gapReduction = m_floatRand(
                                            0.f, (std::min(150u, m_highScore) / 500.f) + 0.05f
                                        );
                                        m_pipes.push_back({ctx.createObject(), ctx.createObject()});
                                        const std::pair<unsigned int, unsigned int> &pipes =
                                            *(m_pipes.end() - 1);
                                        ctx.addAttribute(
                                            pipes.first, ATMA::AttributeType(ATMA::Attribute::Shape)
                                        );
                                        ctx.addAttribute(
                                            pipes.first,
                                            ATMA::AttributeType(ATMA::Attribute::Velocity)
                                        );
                                        ctx.addAttribute(
                                            pipes.first,
                                            ATMA::AttributeType(ATMA::Attribute::Render)
                                        );
                                        ctx.addAttribute(
                                            pipes.first,
                                            ATMA::AttributeType(ATMA::Attribute::Collidable)
                                        );
                                        auto shape = ctx.getAttribute<ATMA::AttrShape>(
                                            pipes.first, ATMA::AttributeType(ATMA::Attribute::Shape)
                                        );
                                        shape->m_pos.x = 1.f;
                                        shape->m_pos.y = 0.8f + middleOffset - (gapReduction / 2);
                                        shape->m_rot = 180.f;
                                        auto vel = ctx.getAttribute<ATMA::AttrVelocity>(
                                            pipes.first,
                                            ATMA::AttributeType(ATMA::Attribute::Velocity)
                                        );
                                        vel->m_dpos.x = -0.01;
                                        auto render = ctx.getAttribute<ATMA::AttrRenderable>(
                                            pipes.first,
                                            ATMA::AttributeType(ATMA::Attribute::Render)
                                        );
                                        render->m_element = m_wallTexture->m_self;
                                        render->m_srcRegion = ATMA::Vec2<float>{1.f, 1.f};
                                        render->m_region = ATMA::Vec2<float>{0.1f, 0.4f};
                                        render->m_srcPos = ATMA::Vec2<float>{0.f, 0.f};
                                        render->m_screenPos =
                                            ATMA::Vec2<float>{1.f, shape->m_pos.y};
                                        render->m_rot = 180.f;
                                        render->m_stackPos = 0;
                                        auto collider = ctx.getAttribute<ATMA::AttrCollidable>(
                                            pipes.first,
                                            ATMA::AttributeType(ATMA::Attribute::Collidable)
                                        );
                                        collider->m_collider.a = ATMA::Vec2<float>{0,0};
                                        collider->m_collider.b = ATMA::Vec2<float>{0,0.3f};
                                        collider->m_collider.r = 0.05f;
                                        collider->m_collider.setBase(ATMA::Vec2<float>{1.f, shape->m_pos.y});
                                        collider->m_collider.setRotation(180.0f);
                                        ctx.addAttribute(
                                            pipes.second,
                                            ATMA::AttributeType(ATMA::Attribute::Shape)
                                        );
                                        ctx.addAttribute(
                                            pipes.second,
                                            ATMA::AttributeType(ATMA::Attribute::Velocity)
                                        );
                                        ctx.addAttribute(
                                            pipes.second,
                                            ATMA::AttributeType(ATMA::Attribute::Render)
                                        );
                                        ctx.addAttribute(
                                            pipes.second,
                                            ATMA::AttributeType(ATMA::Attribute::Collidable)
                                        );
                                        shape = ctx.getAttribute<ATMA::AttrShape>(
                                            pipes.first, ATMA::AttributeType(ATMA::Attribute::Shape)
                                        );
                                        shape->m_pos.x = 1.f;
                                        shape->m_pos.y = -0.8f + middleOffset + (gapReduction / 2);
                                        vel = ctx.getAttribute<ATMA::AttrVelocity>(
                                            pipes.second,
                                            ATMA::AttributeType(ATMA::Attribute::Velocity)
                                        );
                                        vel->m_dpos.x = -0.05;
                                        render = ctx.getAttribute<ATMA::AttrRenderable>(
                                            pipes.second,
                                            ATMA::AttributeType(ATMA::Attribute::Render)
                                        );
                                        render->m_element = m_wallTexture->m_self;
                                        render->m_srcRegion = ATMA::Vec2<float>{1.f, 1.f};
                                        render->m_region = ATMA::Vec2<float>{0.1f, 0.4f};
                                        render->m_srcPos = ATMA::Vec2<float>{0.f, 0.f};
                                        render->m_screenPos =
                                            ATMA::Vec2<float>{1.f, shape->m_pos.y};
                                        render->m_stackPos = 0;
                                        collider = ctx.getAttribute<ATMA::AttrCollidable>(
                                            pipes.second,
                                            ATMA::AttributeType(ATMA::Attribute::Collidable)
                                        );
                                        collider->m_collider.a = ATMA::Vec2<float>{0,0};
                                        collider->m_collider.b = ATMA::Vec2<float>{0,0.3f};
                                        collider->m_collider.r = 0.05f;
                                        collider->m_collider.setBase(ATMA::Vec2<float>{1.f, shape->m_pos.y});
                                        m_lastSpawn = 0;
                                    }
                                }
                            );
                        }
                        else if(!m_started)
                        {
                            m_started = true;
                            ctx.addAttribute(
                                m_playerID, ATMA::AttributeType(ATMA::Attribute::Controllable)
                            );
                            ctx.removeAttribute(
                                m_promptID, ATMA::AttributeType(ATMA::Attribute::Render)
                            );
                            ctx.addAttribute(
                                m_highScoreID, ATMA::AttributeType(ATMA::Attribute::Render)
                            );
                            auto highScoreRender = ctx.getAttribute<ATMA::AttrRenderable>(
                                m_highScoreID, ATMA::AttributeType(ATMA::Attribute::Render)
                            );
                            highScoreRender->m_element = "High Score: 0";
                            highScoreRender->m_region = ATMA::Vec2<float>{0.04f, 0.1f};
                            highScoreRender->m_screenPos = ATMA::Vec2<float>{-0.5f, 0.8f};
                            highScoreRender->m_stackPos = 1;
                        }
                        break;
                    }
                }
                break;
            }
        case ATMA::WindowEventEnum::Resized:
            ATMA::ATMAContext::getContext().m_renderCtx->setSize(
                {l_winEvent.getProp<unsigned int>("width"s),
                 l_winEvent.getProp<unsigned int>("height"s)}
            );
            break;
        case ATMA::WindowEventEnum::Closed:
            l_winEvent.m_win->notifyClose();
            break;
        }
        return;
    }

    /**
     * Triggers any event specific functionality of the system
     * @param l_e event details of the passed event
     */
    virtual void notify(const ATMA::ObjectEventContext &l_e) override
    {
        auto playerVel = ctx.getAttribute<ATMA::AttrVelocity>(
            m_playerID, ATMA::AttributeType(ATMA::Attribute::Velocity)
        );
        playerVel->m_drot = 8.9f;
        m_gameOver = true;
        ctx.addAttribute(m_gameOverID, ATMA::AttributeType(ATMA::Attribute::Render));
        auto gameOverRender = ctx.getAttribute<ATMA::AttrRenderable>(
            m_gameOverID, ATMA::AttributeType(ATMA::Attribute::Render)
        );

        gameOverRender->m_element = "Game Over";
        gameOverRender->m_region = ATMA::Vec2<float>{0.04f, 0.1f};
        gameOverRender->m_screenPos = ATMA::Vec2<float>{-0.3f, 0.22f};
        gameOverRender->m_stackPos = 1;
        ctx.onUpdate([&](const long long &l_dt) {});
    }
private:
    bool m_started{false}, m_gameOver{false};
    unsigned int m_playerID{}, m_promptID{}, m_gameOverID{}, m_highScoreID{}, m_highScore{},
        m_firstPipe{};
    std::shared_ptr<ATMA::Texture> m_playerTexture;
    std::shared_ptr<ATMA::Texture> m_wallTexture;
    std::shared_ptr<ATMA::Font> m_font;
    ATMA::RandomGenerator<float> m_floatRand{};
    long long m_lastSpawn{0};

    std::vector<std::pair<unsigned int, unsigned int>> m_pipes{};
};