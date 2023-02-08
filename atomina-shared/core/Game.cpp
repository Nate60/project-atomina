#include "pch.hpp"
#include "Game.hpp"
#include "util/Log.hpp"
#ifdef ATMA_USE_GLFW
#    include <GLFW/glfw3.h>
#endif

namespace ATMA
{

    Game::Game() {}

    Game::~Game() {}

    void Game::initializeContext()
    {
        auto &ctx = ATMAContext::getContext();
        //--SETUP--//

        Log::Init();

#ifdef ATMA_USE_GLFW
        if(!glfwInit())
            ATMA_ENGINE_ERROR("GLFW failed to initialize!");
#endif

        // attribute registration
        ctx.registerAttributeType<AttrControllable>(AttributeType(Attribute::Controllable));
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