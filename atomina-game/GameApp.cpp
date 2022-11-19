
#include "GameApp.hpp"

GameApp::GameApp() {}

GameApp::~GameApp() {}

void
GameApp::run()
{
    ATMA_ENGINE_INFO("Game is now running");
    active = true;
    ATMA::Window win{};
    ATMA::ATMAContext &ctx = ATMA::ATMAContext::getContext();
    std::unique_ptr<GameState> gameState{new GameState{}};

    while(active)
    {
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
