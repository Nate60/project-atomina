#include "pch.hpp"
#include "Entry.hpp"

/*
 * DLL entry point into execution
 */
namespace ATMA
{
#ifdef _WINDOWS

    BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
    {
        if(fdwReason == DLL_PROCESS_ATTACH)
            OSContextWinImpl::getContext().setDLLInstanceHandle(hinstDLL);
        return true;
    }

    void startGame(std::unique_ptr<Game> l_game)
    {
        // required for winsock
        WSADATA wsaData;
        WSAStartup(MAKEWORD(2, 2), &wsaData);

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
#elif __linux__
}
int main()
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