#include "GameApp.hpp"

GameApp::GameApp() {}

GameApp::~GameApp() {}

void GameApp::run()
{
    ATMA_ENGINE_INFO("Game is now running");
    active = true;

    initializeContext();

    ATMA::ATMAContext &ctx = ATMA::ATMAContext::getContext();
    // std::unique_ptr<GameState> gameState{new GameState{}};

    std::shared_ptr<ATMA::GLRenderContext> glCtx = ATMA::GLRenderContext::makeRenderContext();

    std::shared_ptr<ATMA::AppWindow> win = ATMA::AppWindow::makeWindow();

    win->show();
    win->poll();

    glCtx->setWindow(win);

    std::shared_ptr<ATMA::Renderable> renderable = std::make_shared<ATMA::Renderable>();
    renderable->m_texture = ATMA::GLTexture::makeTexture(
        "C:\\Users\\Sixti\\Source\\Repos\\project-atomina\\res\\shaggysheet.png"
    );
    renderable->m_region = {1, 1};

    glCtx->draw(renderable);
    win->swapBuffers();
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
