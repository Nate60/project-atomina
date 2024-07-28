#include "GameApp.hpp"

GameApp::GameApp() {}

GameApp::~GameApp() {}

void GameApp::run()
{
    ATMA_ENGINE_INFO("Game is now running");
    active = true;

    initializeContext();

    ATMA::ATMAContext &ctx = ATMA::ATMAContext::getContext();

    ctx.addSystemType<SysFly>(ATMA::SysType(ATMA::System::COUNT));

    auto winID = ctx.createWindow();
    auto win = ctx.getWindow(winID);
    auto renderer = ctx.getRenderer();
    win->setSize({1920, 1080});

    win->show();
    // note that the context is reset when set to a new window, so any memory associated with
    // it will cause an error. So best to set window before anything else
    renderer->setWindow(win);
    auto vertShaderID = ctx.registerResource("vertex", 1u, "shader/defaultVertex.shader");
    auto fragShaderID = ctx.registerResource("frag", 1u, "shader/defaultFrag.shader");

    std::shared_ptr<MainMenuState> state =
        std::make_shared<MainMenuState>(win, vertShaderID, fragShaderID);
    std::shared_ptr<PlayState> playState = std::make_shared<PlayState>(vertShaderID, fragShaderID);

    auto sysFly = ctx.getSystem<SysFly>(ATMA::SysType(ATMA::System::COUNT));
    ctx.addObjectEventListener(GameEventType(GameEventEnum::FLAP), sysFly);

    ctx.addState(GameStateType(GameStateEnum::MAINMENU), std::move(state));
    ATMA_ENGINE_INFO("Created mainmenu");
    ctx.addState(GameStateType(GameStateEnum::PLAYSTATE), std::move(playState));
    ATMA_ENGINE_INFO("Created playstate");

    ATMA_ENGINE_INFO("Starting Game Loop");

    while(!win->shouldClose())
    {
        win->poll();
        renderer->startScene(ATMA::GLCamera{
            {0.f,0.f},
            {10.f,10.f}
        });
        ctx.update();
        renderer->finishScene();
        win->swapBuffers();
    }
}

void GameApp::shutdown()
{
    ATMA_ENGINE_INFO("Shutting down game");
    active = false;
}

std::unique_ptr<ATMA::Game> ATMA::CreateGame()
{
    return std::unique_ptr<ATMA::Game>{new GameApp()};
}