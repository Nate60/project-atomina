#include <memory>
#ifndef ATMA_SERVER
#    include "GameApp.hpp"
#    include "state/RunState.hpp"

GameApp::GameApp() {}

GameApp::~GameApp() {}

void GameApp::setup(ATMA::ATMAContext *l_ctx)
{
    active = true;

    auto winID = l_ctx->m_winMan->createWindow(l_ctx);
    m_win = l_ctx->m_winMan->getWindow(winID);
    m_win->setSize({1920, 1080});

    m_win->show();
    // note that the context is reset when set to a new window, so any memory associated with
    // it will cause an error. So best to set window before anything else
    l_ctx->m_renderer->setWindow(m_win);
    auto fontID = l_ctx->m_resMan->registerResource("font", 0u, "res/defaultFont.png");
    l_ctx->m_renderer->toggleBlend(true);
    std::shared_ptr<RunState> runState = std::make_shared<RunState>(l_ctx);
    l_ctx->m_stateMan->addState(l_ctx, 0u, runState);
}

void GameApp::update(ATMA::ATMAContext *l_ctx, const double &l_dt)
{
    if(m_win->shouldClose())
    {
        active = false;
    }

    m_win->poll();
    l_ctx->m_renderer->startScene(
        ATMA::GLCamera{
            {  0.f,   0.f},
            {320.f, 180.f}
    }
    );
    l_ctx->m_sysMan->update(l_ctx, l_dt);
    l_ctx->m_renderer->finishScene();
    m_win->swapBuffers();
}

void GameApp::shutdown(ATMA::ATMAContext *l_ctx)
{
    ATMA_ENGINE_INFO("Shutting down game");
}

std::unique_ptr<ATMA::Game> ATMA::CreateGame()
{
    return std::unique_ptr<ATMA::Game>{new GameApp()};
}

#endif
