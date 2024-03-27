#include "GameApp.hpp"

GameApp::GameApp() {}

GameApp::~GameApp() {}

void GameApp::run()
{
    ATMA_ENGINE_INFO("Game is now running");
    active = true;

    initializeContext();

    ATMA::ATMAContext &ctx = ATMA::ATMAContext::getContext();
    ATMA_ENGINE_INFO("Executing Directory: {0}", ATMA::Path::getRootPath().generic_string());
    ATMA::Path shaggyPath = ATMA::Path{"res/shaggysheet.png"};
    ATMA_ENGINE_INFO("ShaggyPath: {0}", shaggyPath.toString());

    std::shared_ptr<ATMA::GLRenderContext> glCtx = ATMA::GLRenderContext::makeRenderContext();

    std::shared_ptr<ATMA::AppWindow> win = ATMA::AppWindow::makeWindow();

    win->show();

    glCtx->setWindow(win);

    std::shared_ptr<ATMA::GLRenderable> renderable = std::make_shared<ATMA::GLRenderable>();
    renderable->m_texture = ATMA::GLTexture::makeTexture(shaggyPath.toString());
    renderable->m_region = {1.5f, 2.5f};

    while(!win->shouldClose())
    {
        win->poll();
        glCtx->clear();
        glCtx->draw(renderable);
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
