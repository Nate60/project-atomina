#include "pch.hpp"
#include "Entry.hpp"
#include "ATMAContext.hpp"


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
        app->initializeContext();
        auto &ctx = ATMA::ATMAContext::getContext();
        ATMA_ENGINE_INFO("Setting up application");
        app->setup(ctx);
        ATMA_ENGINE_INFO("Starting game loop");
        while (app->active)
        {
            app->update(ctx);
        }
        ATMA_ENGINE_INFO("Ending game loop, shutting down application");
        app->shutdown(ctx);
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