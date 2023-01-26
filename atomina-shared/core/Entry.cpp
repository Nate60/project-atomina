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
        Log::Init();
        ATMA_ENGINE_INFO("Init logger!");
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