#include "GameApp.hpp"

GameApp::GameApp() {}

GameApp::~GameApp() {}

static void
key_callback(ATMA::Window *window, int key, int scancode, int action, int mods)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        window->setWindowShouldClose(true);
}

void
GameApp::run()
{
    ATMA_ENGINE_INFO("Game is now running");
    active = true;

    initializeContext();

    ATMA::ATMAContext &ctx = ATMA::ATMAContext::getContext();
    std::unique_ptr<GameState> gameState{new GameState{}};

    auto win = ctx.getWindow(ATConst::MAIN_WINDOW_ID);

    auto shutdownManager =
        std::make_shared<ShutDownManager>(ShutDownManager(std::bind(&GameApp::shutdown, this)));
    ctx.addObjectEventListener(ATMA::ObjectEventType(ATMA::ObjectEvent::ShutDown), shutdownManager);

    win->setInputCallback(key_callback);

    // register resources

    // add states
    ctx.addState(ATMA::StateType(ATMA::State::COUNT), std::move(gameState));

    while(active)
    {

        win->swapBuffers();
        win->pollEvents();
        if(win->getWindowShouldClose())
            ctx.dispatchObjectEvent({ATMA::ObjectEventType(ATMA::ObjectEvent::ShutDown)});
        ctx.update();
    }
}

void
GameApp::shutdown()
{
    ATMA_ENGINE_INFO("Shutting down game");
    active = false;
}

#ifdef _WINDOWS
int
main()
{
    ATMA::startGame(std::unique_ptr<ATMA::Game>(new GameApp{}));
}
#else
std::unique_ptr<ATMA::Game>
ATMA::CreateGame()
{
    return std::unique_ptr<ATMA::Game>{new GameApp()};
}
#endif
