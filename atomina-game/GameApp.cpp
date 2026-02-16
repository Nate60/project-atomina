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
    l_ctx->m_renderer->toggleBlend(true);
    l_ctx->m_renderer->toggleDepthTest(false);
    auto vertID = l_ctx->m_resMan->registerResource("vertex", 1u, "shader/defaultVertex.shader");
    auto fragID = l_ctx->m_resMan->registerResource("frag", 1u, "shader/defaultFrag.shader");
    auto vert = l_ctx->m_resMan->loadResource<ATMA::GLShader>(l_ctx, vertID);
    auto frag = l_ctx->m_resMan->loadResource<ATMA::GLShader>(l_ctx, fragID);
    vert->compile(ATMA::ShaderType::Vertex);
    frag->compile(ATMA::ShaderType::Fragment);
    auto prog = ATMA::GLProgram::makeProgram();
    prog->attachShader(vert);
    prog->attachShader(frag);
    prog->link();
    l_ctx->m_renderer->m_ctx->setShaderProgram(prog);
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
        ATMA::Camera{
            {  0.f,   0.f},
            {320.f, 180.f}
    }
    );
    l_ctx->m_sysMan->update(l_ctx, l_dt);
    l_ctx->m_renderer->finishScene(l_ctx);
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
