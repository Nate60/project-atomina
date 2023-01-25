#include "pch.hpp"
#include "Game.hpp"

namespace ATMA
{

    Game::Game() {}

    Game::~Game() {}

    void Game::initializeContext()
    {
        auto &ctx = ATMAContext::getContext();
            //--SETUP--//

        // attribute registration
        ctx.registerAttributeType<AttrControllable>(
            AttributeType(Attribute::Controllable)
        );
        ctx.registerAttributeType<AttrPosition>(AttributeType(Attribute::Position));
        ctx.registerAttributeType<AttrVelocity>(AttributeType(Attribute::Velocity));

        // system registration
        ctx.addSystemType<SysController>(SystemType(System::Controller));
        ctx.addSystemType<SysTranslator>(SystemType(System::Translator));

    }

    void Game::run()
    {

        active = true;
    }

    void Game::shutdown() {}
}