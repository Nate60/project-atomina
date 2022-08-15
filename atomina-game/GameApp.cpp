
#include "GameApp.hpp"
#include "OAS/Attribute.hpp"
#include "OAS/SysBase.hpp"
#include "OAS/attributes/AttrAnimatable.hpp"
#include "OAS/attributes/AttrDrawable.hpp"
#include "OAS/attributes/AttrTranslatable.hpp"
#include "OAS/systems/SysAnimator.hpp"
#include "OAS/systems/SysController.hpp"
#include "OAS/systems/SysRenderer.hpp"
#include "core/ATMAContext.hpp"
#include "event/CallBackKey.hpp"
#include "event/EventContext.hpp"
#include "util/Log.hpp"

GameApp::GameApp() {}

GameApp::~GameApp() {}

void
GameApp::run()
{
    ATMA_ENGINE_INFO("Game is now running");
    active = true;
    ATMA::Window win{};
    ATMA::ATMAContext &ctx = ATMA::ATMAContext::getContext();
    std::unique_ptr<GameState> gameState{new GameState{}};

    ctx.addState(ATMA::StateType(ATMA::State::COUNT), std::move(gameState));
    ctx.addSystemType<ATMA::SysRenderer>(ATMA::SystemType(ATMA::System::Renderer));
    ctx.addSystemType<ATMA::SysAnimator>(ATMA::SystemType(ATMA::System::Animator));
    ctx.registerAttributeType<ATMA::AttrTranslatable>(ATMA::AttrType(ATMA::Attribute::Translatable)
    );
    ctx.registerAttributeType<ATMA::AttrDrawable>(ATMA::AttrType(ATMA::Attribute::Drawable));
    ctx.registerAttributeType<ATMA::AttrAnimatable>(ATMA::AttrType(ATMA::Attribute::Animatable));
    auto objID = ctx.createObject();
    ctx.addAttribute(objID, ATMA::AttrType(ATMA::Attribute::Translatable));
    ctx.addAttribute(objID, ATMA::AttrType(ATMA::Attribute::Drawable));
    ctx.addAttribute(objID, ATMA::AttrType(ATMA::Attribute::Animatable));
    auto sysRenderer = ctx.getSystem<ATMA::SysRenderer>(ATMA::SystemType(ATMA::System::Renderer));
    auto attrDraw =
        ctx.getAttribute<ATMA::AttrDrawable>(objID, ATMA::AttrType(ATMA::Attribute::Drawable));
    auto attrTrans = ctx.getAttribute<ATMA::AttrTranslatable>(
        objID, ATMA::AttrType(ATMA::Attribute::Translatable)
    );
    attrTrans->m_x = 100;
    attrTrans->m_y = 100;
    attrDraw->m_sprite.scale({4.f, 4.f});
    // attrDraw->m_sprite.setColor(sf::Color::Magenta);

    for(;;)
    {
        ATMA::EventContext e = win.popEvent();
        sf::Event sfE = e.m_sfEvent.value_or(sf::Event{});

        if(sfE.type == sf::Event::EventType::KeyPressed
           || sfE.type == sf::Event::EventType::KeyReleased)
        {
            if(sfE.key.code == sf::Keyboard::Escape)
            {
                ATMA_ENGINE_INFO("Escape key pressed");
                break;
            }
        }
        ctx.update();
        win.clear();
        win.draw(*sysRenderer);
        win.display();
    }
}

void
GameApp::shutdown()
{
    ATMA_ENGINE_INFO("Shutting down game");
    active = false;
}

std::unique_ptr<ATMA::Game>
ATMA::CreateGame()
{
    return std::unique_ptr<ATMA::Game>{new GameApp()};
}
