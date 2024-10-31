#include "GameApp.hpp"

GameApp::GameApp() {}

GameApp::~GameApp() {}

void GameApp::setup(ATMA::ATMAContext &l_ctx) 
{
    active = true;

    l_ctx.addSystemType<SysFly>(ATMA::SysType(ATMA::System::COUNT));

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

    std::shared_ptr<MainMenuState> state =
        std::make_shared<MainMenuState>(m_win, vertShaderID, fragShaderID);
    std::shared_ptr<PlayState> playState = std::make_shared<PlayState>(vertShaderID, fragShaderID);

    auto sysFly = l_ctx.getSystem<SysFly>(ATMA::SysType(ATMA::System::COUNT));
    l_ctx.addObjectEventListener(GameEventType(GameEventEnum::FLAP), sysFly);
    l_ctx.addObjectEventListener(GameEventType(GameEventEnum::GAMEOVER), playState);
    l_ctx.addObjectEventListener(ATMA::ObjectEventType(ATMA::ObjectEvent::Collision), playState);

    l_ctx.addState(GameStateType(GameStateEnum::MAINMENU), std::move(state));
    ATMA_ENGINE_INFO("Created mainmenu");
    l_ctx.addState(GameStateType(GameStateEnum::PLAYSTATE), std::move(playState));
    ATMA_ENGINE_INFO("Created playstate");
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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