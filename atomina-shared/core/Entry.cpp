#include "pch.hpp"
#include "Entry.hpp"

/*
 * DLL entry point into execution
 */
#ifdef _WINDOWS
namespace ATMA
{
    void startGame(std::unique_ptr<Game> l_game)
    {
        WSADATA wsaData;
        WSAStartup(MAKEWORD(2, 2), &wsaData);

        Log::Init();
        ATMA_ENGINE_INFO("Init logger!");

#    ifdef ATMA_USE_GLFW
        if(!glfwInit())
            ATMA_ENGINE_ERROR("GLFW failed to initialize!");
        ATMA_ENGINE_INFO("Initialized GLFW");
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#    endif

        try
        {
            l_game->run();
        }
        catch(AtominaException e)
        {
            ATMA_ENGINE_ERROR("Fatal error {0} shutting down...", e.what());
        }
        catch(std::exception e)
        {
            ATMA_ENGINE_ERROR("Fatal error {0} shutting down...", e.what());
        }
    }
}
#else
int
main()
{
    ATMA::Log::Init();
    ATMA_ENGINE_INFO("Init logger!");

#    ifdef ATMA_USE_GLFW
    if(!glfwInit())
        ATMA_ENGINE_ERROR("GLFW failed to initialize!");
    ATMA_ENGINE_INFO("Initialized GLFW");
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#    endif
    std::unique_ptr<ATMA::Game> app = ATMA::CreateGame();
    try
    {
        app->run();
    }
    catch(ATMA::AtominaException e)
    {
        ATMA_ENGINE_ERROR("Fatal error {0} shutting down...", e.what());
    }
    catch(std::exception e)
    {
        ATMA_ENGINE_ERROR("Fatal error {0} shutting down...", e.what());
    }
}
#endif