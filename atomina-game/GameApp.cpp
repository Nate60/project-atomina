
#include "GameApp.hpp"
#include <memory>

GameApp::GameApp() {}

GameApp::~GameApp() {}

void
GameApp::run()
{
    ATMA_ENGINE_INFO("Game is now running");
    active = true;

    ATMA::ATMAContext &ctx = ATMA::ATMAContext::getContext();
    std::unique_ptr<GameState> gameState{new GameState{}};

    initializeContext();

    auto shutdownManager =
        std::make_shared<ShutDownManager>(ShutDownManager(std::bind(&GameApp::shutdown, this)));
    ctx.addObjectEventListener(ATMA::ObjectEventType(ATMA::ObjectEvent::ShutDown), shutdownManager);

    // register resources

    // add states
    ctx.addState(ATMA::StateType(ATMA::State::COUNT), std::move(gameState));
    while(active)
    {
        ctx.update();
    }
}

void
GameApp::shutdown()
{
    ATMA_ENGINE_INFO("Shutting down game");
    active = false;
}

#ifdef _WINDOWS
int
main()
{
    ATMA::startGame(std::unique_ptr<ATMA::Game>(new GameApp{}));
}
#else
std::unique_ptr<ATMA::Game>
ATMA::CreateGame()
{
    return std::unique_ptr<ATMA::Game>{new GameApp()};
}
#endif
