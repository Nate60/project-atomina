#include "pch.hpp"
#include "Entry.hpp"


/*
 * Lib entry point into execution
 * 
 */
int main()
{
    #ifdef _WINDOWS
    // required for winsock
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    #endif

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