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
    auto fontid = ctx.registerResource("testfont", 2, "res\\defaultFont.png");

    auto vertShader = ctx.loadResource<ATMA::ShaderGLADImpl>(vertid);
    auto fragShader = ctx.loadResource<ATMA::ShaderGLADImpl>(fragid);
    auto text = ctx.loadResource<ATMA::TextureGLADImpl>(textid);
    auto font = ctx.loadResource<ATMA::Font>(fontid);

    // count in layout, count in row, offset
    auto vertArray = ATMA::VertexArray::makeBuffer({
        {2, 8, 0}, //  pos (x,y)
        {4, 8, 2}, //  colour (r,g,b,a)
        {2, 8, 6}  // 2D Texture pos (x,y)
    });

    auto vertBuf = ATMA::VertexBuffer::makeBuffer({1.f,  1.f,  1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
                                                   1.f,  -1.f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
                                                   -1.f, -1.f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
                                                   -1.f, 1.f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f});

    auto indexBuf = ATMA::IndexBuffer::makeBuffer({0, 1, 2, 0, 2, 3});

    auto shaderProgram = ATMA::ShaderProgram::makeProgram();

    vertArray->bind();

    indexBuf->bind();

    vertBuf->bind();

    vertArray->bindLayout();

    text->bind();
    // font->bindCharacter('C');

    vertShader->compile(ATMA::ShaderType::Vertex);
    fragShader->compile(ATMA::ShaderType::Fragment);

    shaderProgram->attachShader(vertShader);
    shaderProgram->attachShader(fragShader);
    shaderProgram->link();

    while(active)
    {
        shaderProgram->exec();
        shaderProgram->setUniformMat3f("u_transform", ATMA::translationMatrix<float>(0.f, 0.f));
        ctx.draw(vertArray, indexBuf, shaderProgram);
        shaderProgram->setUniformMat3f("u_transform", ATMA::translationMatrix<float>(1.f, 0.5f));
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
