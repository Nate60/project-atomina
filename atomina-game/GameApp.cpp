#include "OAS/attributes/AttrRenderable.hpp"
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
    auto fontID = l_ctx->m_resMan->registerResource("fontfps", 1u, "res/defaultFont.png");
    auto font = l_ctx->m_resMan->loadResource<ATMA::GLTexture>(l_ctx, fontID);
    l_ctx->m_renderer->m_ctx->setShaderProgram(prog);
    m_fpsObj = l_ctx->m_attrMan->createObject();
    l_ctx->m_attrMan->addAttribute(l_ctx, m_fpsObj, ATMA::AttributeType(ATMA::Attribute::Renderable));
    m_fpsText = std::make_shared<ATMA::Text>(ATMA::Text{
        {"FPS:0", {-155.f, 85.f}, {9.f, 9.f}, {5.f, 5.f}}
    });
    m_fpsText->m_texture = font;
    auto attr = l_ctx->m_attrMan->getAttribute<ATMA::AttrRenderable>(
        m_fpsObj, ATMA::AttributeType(ATMA::Attribute::Renderable)
    );
    attr->m_self = m_fpsText;
    std::shared_ptr<RunState> runState = std::make_shared<RunState>(l_ctx);
    l_ctx->m_stateMan->addState(l_ctx, 0u, runState);
}

void GameApp::update(ATMA::ATMAContext *l_ctx, const double &l_dt)
{
    acc += l_dt;
    if(acc >= 1)
    {
        acc = 0;
        m_fpsText->setText("FPS:" + std::to_string((int)(1 / l_dt)));
    }
    if(m_win->shouldClose())
    {
        active = false;
    }
    m_win->poll();
    l_ctx->m_renderer->startScene(ATMA::Camera{
        {  0.f,   0.f},
        {320.f, 180.f}
    });
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
