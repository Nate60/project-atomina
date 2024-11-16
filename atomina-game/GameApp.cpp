#ifndef ATMA_SERVER
#include "GameApp.hpp"

GameApp::GameApp() {}

GameApp::~GameApp() {}

void GameApp::setup(ATMA::ATMAContext &l_ctx) 
{
    active = true;

    auto winID = l_ctx.createWindow();
    m_win = l_ctx.getWindow(winID);
    m_renderer = l_ctx.getRenderer();
    m_win->setSize({1920, 1080});

    m_win->show();
    // note that the context is reset when set to a new window, so any memory associated with
    // it will cause an error. So best to set window before anything else
    m_renderer->setWindow(m_win);
    auto vertShaderID = l_ctx.registerResource("vertex", 1u, "shader/defaultVertex.shader");
    auto fragShaderID = l_ctx.registerResource("frag", 1u, "shader/defaultFrag.shader");

    m_renderer->toggleBlend(true);
    m_conn.connect();
    
}

void GameApp::update(ATMA::ATMAContext &l_ctx)
{
    if (m_win->shouldClose())
    {
        active = false;
    }

    m_win->poll();
    m_renderer->startScene(ATMA::GLCamera{
        {0.f,0.f},
        {360.f,360.f}
    });
    l_ctx.update();
    m_renderer->finishScene();
    m_win->swapBuffers();

}

void GameApp::shutdown(ATMA::ATMAContext &l_ctx)
{
    ATMA_ENGINE_INFO("Shutting down game");
}

std::unique_ptr<ATMA::Game> ATMA::CreateGame()
{
    return std::unique_ptr<ATMA::Game>{new GameApp()};
}
#endif