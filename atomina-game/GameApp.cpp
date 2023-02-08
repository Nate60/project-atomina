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

    auto id = ctx.createObject();
    ctx.addAttribute(id, ATMA::AttributeType(ATMA::Attribute::Position));
    ctx.addAttribute(id, ATMA::AttributeType(ATMA::Attribute::Sprite));
    ctx.addAttribute(id, ATMA::AttributeType(ATMA::Attribute::Renderable));
    auto fragid = ctx.registerResource("test", 0, "shader\\defaultFrag.shader");
    auto vertid = ctx.registerResource("test", 0, "shader\\defaultVertex.shader");
    auto textid = ctx.registerResource("testimage", 1, "res\\shaggysheet.png");

    auto vertShader = ctx.loadResource<ATMA::ShaderGLADImpl>(vertid);
    auto fragShader = ctx.loadResource<ATMA::ShaderGLADImpl>(fragid);
    auto text = ctx.loadResource<ATMA::TextureGLADImpl>(textid);

    auto vertArray = ATMA::VertexArray::makeBuffer({
        {3, 8, 0},
        {3, 8, 3},
        {2, 8, 6}
    });

    auto vertBuf =
        ATMA::VertexBuffer::makeBuffer({0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
                                        0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
                                        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
                                        -0.5f, 0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f});

    auto indexBuf = ATMA::IndexBuffer::makeBuffer({0, 1, 2, 0, 2, 3});

    auto shaderProgram = ATMA::ShaderProgram::makeProgram();

    vertArray->bind();

    indexBuf->bind();

    vertBuf->bind();

    vertArray->bindLayout();

    text->bind();

    vertShader->compile(ATMA::ShaderType::Vertex);
    fragShader->compile(ATMA::ShaderType::Fragment);

    shaderProgram->attachShader(vertShader);
    shaderProgram->attachShader(fragShader);
    shaderProgram->link();

    while(active)
    {
        ctx.draw(vertArray, indexBuf, shaderProgram);
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
