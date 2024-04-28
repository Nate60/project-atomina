#include "GameApp.hpp"

using namespace std::string_literals;

GameApp::GameApp() {}

GameApp::~GameApp() {}

void GameApp::run()
{
    ATMA_ENGINE_INFO("Game is now running");
    active = true;

    initializeContext();

    ATMA::ATMAContext &ctx = ATMA::ATMAContext::getContext();

    std::shared_ptr<ATMA::AppWindow> win = ATMA::AppWindow::makeWindow();

    win->show();
    //note that the context is reset when set to a new window, so any memory associated with
    //it will cause an error. So best to set window before anything else
    ctx.m_renderCtx->setWindow(win);

    std::unique_ptr<MainMenuState> state = std::make_unique<MainMenuState>(win);

    ctx.addState(GameStateType(GameStateEnum::MAINMENU), std::move(state));

    ATMA_ENGINE_INFO("Starting Game Loop");
    while(!win->shouldClose())
    {
        win->poll();
        ctx.m_renderCtx->clear();
        ctx.update();
        ctx.m_renderCtx->draw();
        win->swapBuffers();
    }
}

void GameApp::shutdown()
{
    ATMA_ENGINE_INFO("Shutting down game");
    active = false;
}

#ifdef _WINDOWS
int main()
{
    ATMA::startGame(std::unique_ptr<ATMA::Game>(new GameApp{}));
}
#else
std::unique_ptr<ATMA::Game> ATMA::CreateGame()
{
    return std::unique_ptr<ATMA::Game>{new GameApp()};
}
#endif
