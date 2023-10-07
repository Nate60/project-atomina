#include "GameApp.hpp"

GameApp::GameApp() {}

GameApp::~GameApp() {}

void GameApp::run()
{
    ATMA_ENGINE_INFO("Game is now running");
    active = true;

    initializeContext();

    ATMA::ATMAContext &ctx = ATMA::ATMAContext::getContext();
    std::unique_ptr<GameState> gameState{new GameState{}};

    auto shutdownManager =
        std::make_shared<ShutDownManager>(ShutDownManager(std::bind(&GameApp::shutdown, this)));
    ctx.addObjectEventListener(ATMA::ObjectEventType(ATMA::ObjectEvent::ShutDown), shutdownManager);

    // register resources
    std::shared_ptr<ATMA::Renderable> renderable = std::make_shared<ATMA::Renderable>(
        ATMA::Vec2{0, 0},
        ATMA::Vec2{100, 100},
        ATMA::GLTexture::makeTexture("res\\shaggysheet.png"),
        ATMA::GLShader::makeShader("shader\\defaultFrag.shader"),
        ATMA::GLShader::makeShader("shader\\defaultVertext.shader")
    );

    std::shared_ptr<ATMA::AppWindow> window = ATMA::AppWindow::makeWindow();

    ctx.getRenderer().setWindow(window);

    window->show();

    // add states
    ctx.addState(ATMA::StateType(ATMA::State::COUNT), std::move(gameState));

    while(!window->shouldClose())
    {
        window->poll();
        ctx.getRenderer().draw(renderable);
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
