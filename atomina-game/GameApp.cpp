
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

    // create window
    auto winID = ctx.createWindow();
    auto win = ctx.getWindow(winID);
    // get renderer
    auto renderer = ctx.getSystem<ATMA::SysRenderer>(ATMA::SystemType(ATMA::System::Renderer));

    while(active)
    {
        ctx.update();
        win->draw(*renderer);
        win->display();
    }
}

void
GameApp::shutdown()
{
    ATMA_ENGINE_INFO("Shutting down game");
    active = false;
}

std::unique_ptr<ATMA::Game>
ATMA::CreateGame()
{
    return std::unique_ptr<ATMA::Game>{new GameApp()};
}
