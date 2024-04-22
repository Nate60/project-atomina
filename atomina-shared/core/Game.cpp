#include "pch.hpp"
#include "Game.hpp"
#include "util/Log.hpp"

namespace ATMA
{

    Game::Game() {}

    Game::~Game() {}

    void Game::initializeContext()
    {
        //--SETUP--//

        auto &ctx = ATMAContext::getContext();

        // attribute registration
        ctx.registerAttributeType<AttrControllable>(AttributeType(Attribute::Controllable));
        ctx.registerAttributeType<AttrShape>(AttributeType(Attribute::Shape));
        ctx.registerAttributeType<AttrVelocity>(AttributeType(Attribute::Velocity));
        ctx.registerAttributeType<AttrRenderable>(AttributeType(Attribute::Render));

        // system registration
        ctx.addSystemType<SysController>(SystemType(System::Controller));
        ctx.addSystemType<SysTranslator>(SystemType(System::Translator));
        ctx.addSystemType<SysRenderer>(SystemType(System::Renderer));
    }

    void Game::run()
    {

        active = true;
    }

    void Game::shutdown() {}
}