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
    std::unique_ptr<ATMA::GLRenderContext> glCtx = ATMA::GLRenderContext::makeRenderContext();

    auto textID = ctx.registerResource("shaggyhead", 0u, "res/shaggysheet.png");
    auto fontID = ctx.registerResource("font", 1u, "res/defaultFont.png");

    std::shared_ptr<ATMA::AppWindow> win = ATMA::AppWindow::makeWindow();

    win->show();

    glCtx->setWindow(win);
    glCtx->setFont(ctx.loadResource<ATMA::Font>(fontID));
    std::shared_ptr<ATMA::GLRenderable> renderable = std::make_shared<ATMA::GLRenderable>();
    renderable->m_texture = ctx.loadResource<ATMA::Texture>(textID)->m_self;
    renderable->m_region = {1.5f, 2.5f};
    renderable->m_srcRegion = {1.0f, 1.0f};

    win->addCallback(
        ATMA::WindowEventEnum::Resize,
        [&glCtx](ATMA::WindowEvent we)
        {
            ATMA::Vec2 v{we.get<unsigned int>("width"), we.get<unsigned int>("height")};
            we.m_win->setSize(v);
            glCtx->setSize(v);
        }
    );

    win->addCallback(
        ATMA::WindowEventEnum::Close, [](ATMA::WindowEvent we) { we.m_win->notifyClose(); }
    );

    ATMA_ENGINE_INFO("Starting Game Loop");
    while(!win->shouldClose())
    {
        win->poll();
        glCtx->clear();
        glCtx->draw(renderable);
        glCtx->drawText("What is up", {-0.7f, 0.2f}, {0.05f, 0.05f});
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
