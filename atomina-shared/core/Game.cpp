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
        ctx.registerAttributeType<AttrSprite>(AttributeType(Attribute::Sprite));
        ctx.registerAttributeType<AttrRenderable>(AttributeType(Attribute::Renderable));
        ctx.registerAttributeType<AttrText>(AttributeType(Attribute::Text));

        // system registration
        ctx.addSystemType<SysController>(SystemType(System::Controller));
        ctx.addSystemType<SysTranslator>(SystemType(System::Translator));
        ctx.addSystemType<SysRenderer>(SystemType(System::Renderer));
        ctx.addSystemType<SysTextRenderer>(SystemType(System::TextRenderer));
    }

    void Game::run()
    {

        active = true;
    }

    void Game::shutdown() {}
}