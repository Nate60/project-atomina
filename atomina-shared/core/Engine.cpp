#include "pch.hpp"
#include "Engine.hpp"
#include "ATMAContext.hpp"

/*
 * Lib entry point into execution
 *
 */
int main(int argc, char **argv)
{
#ifdef _WINDOWS
    // required for winsock
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif

    ATMA::Log::Init();
    ATMA_ENGINE_INFO("Init logger!");
#ifdef ATMA_SERVER
    std::unique_ptr<ATMA::Server> app = ATMA::CreateServer();
#else
    std::unique_ptr<ATMA::Game> app = ATMA::CreateGame();
#endif
    try
    {
        std::chrono::steady_clock engineClock{};
        std::chrono::time_point<std::chrono::steady_clock> lastUpdate = engineClock.now();
        auto ctx = app->initializeContext();
        ATMA_ENGINE_INFO("Setting up application");
        ctx->argc = &argc;
        ctx->argv = argv;
        app->setup(ctx);
        ATMA_ENGINE_INFO("Starting game loop");
        while(app->active)
        {
            std::chrono::duration<double> dt = engineClock.now() - lastUpdate;
            lastUpdate = engineClock.now();
            app->update(ctx, dt.count());
        }
        ATMA_ENGINE_INFO("Ending game loop, shutting down application");
        app->shutdown(ctx);
        app->destoryContext(ctx);
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
