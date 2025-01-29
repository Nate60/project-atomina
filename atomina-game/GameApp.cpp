#ifndef ATMA_SERVER
#    include "GameApp.hpp"

GameApp::GameApp() {}

GameApp::~GameApp() {}

void GameApp::setup(ATMA::ATMAContext &l_ctx)
{
    l_ctx.m_attrMan->registerAttributeType<AttrConnection>(GameAttributeType(GameAttributeEnum::CONNECTION));
    l_ctx.m_sysMan->addSystemType<SysConnection>(GameSystemType(GameSystemEnum::CONNECTION));
    l_ctx.m_attrMan->registerAttributeType<AttrTimer>(GameAttributeType(GameAttributeEnum::TIMER));
    l_ctx.m_sysMan->addSystemType<SysTime>(GameSystemType(GameSystemEnum::TIME));
    auto netSys = l_ctx.m_sysMan->getSystem<SysConnection>(GameSystemType(GameSystemEnum::CONNECTION));
    l_ctx.m_netMan->addMessageListener(ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::CONNECTION_STARTED), netSys);
    l_ctx.m_netMan->addMessageListener(ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::PORT_JOIN), netSys);
    l_ctx.m_netMan->addMessageListener(ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::PORT_REQUEST), netSys);
    l_ctx.m_netMan->addMessageListener(ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::PORT_RESPONSE), netSys);
    l_ctx.m_netMan->addMessageListener(ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::STATE_CHANGE), netSys);
    l_ctx.m_netMan->addMessageListener(GameNetMessageType(GameNetMessageEnum::PLAYER_WIN), netSys);
    l_ctx.m_netMan->addMessageListener(GameNetMessageType(GameNetMessageEnum::PLAYER_TIED), netSys);
    l_ctx.m_netMan->addMessageListener(GameNetMessageType(GameNetMessageEnum::PLAYER_LOSE), netSys);
    active = true;

    auto winID = l_ctx.m_winMan->createWindow();
    m_win = l_ctx.m_winMan->getWindow(winID);
    m_win->setSize({1920, 1080});

    m_win->show();
    // note that the context is reset when set to a new window, so any memory associated with
    // it will cause an error. So best to set window before anything else
    l_ctx.m_renderer->setWindow(m_win);
    auto vertShaderID = l_ctx.m_resMan->registerResource("vertex", 1u, "shader/defaultVertex.shader");
    auto fragShaderID = l_ctx.m_resMan->registerResource("frag", 1u, "shader/defaultFrag.shader");
    auto fontID = l_ctx.m_resMan->registerResource("font", 0u, "res/defaultFont.png");
    std::shared_ptr<MainMenuState> state = std::make_shared<MainMenuState>(m_win, vertShaderID, fragShaderID, fontID);
    l_ctx.m_stateMan->addState(GameStateType(GameStateEnum::MAINMENU), std::move(state));
    std::shared_ptr<LobbyState> lobby = std::make_shared<LobbyState>(m_win, vertShaderID, fragShaderID, fontID);
    l_ctx.m_eventMan->addObjectEventListener(ATMA::ObjectEventType(ATMA::ObjectEvent::Network), lobby);
    l_ctx.m_stateMan->addState(GameStateType(GameStateEnum::LOBBY), std::move(lobby));
    std::shared_ptr<PlayState> play = std::make_shared<PlayState>(m_win, vertShaderID, fragShaderID, fontID);
    l_ctx.m_eventMan->addObjectEventListener(ATMA::ObjectEventType(ATMA::ObjectEvent::Network), play);
    l_ctx.m_eventMan->addObjectEventListener(GameEventType(GameEventEnum::TIMER_COMPLETE), play);
    l_ctx.m_stateMan->addState(GameStateType(GameStateEnum::PLAYSTATE), std::move(play));
    l_ctx.m_renderer->toggleBlend(true);
    auto id = l_ctx.m_resMan->registerResource("testWave", 0u, std::optional<std::string>{"res/test.wav"});
    auto channelId = l_ctx.m_audioMan->createAudioChannel();
    auto channel = l_ctx.m_audioMan->getChannel(channelId);
    channel->playNow(id);
}

void GameApp::update(ATMA::ATMAContext &l_ctx, const long long &l_dt)
{
    if(m_win->shouldClose())
    {
        active = false;
    }

    m_win->poll();
    l_ctx.m_sysMan->update(l_ctx, l_dt);
    l_ctx.m_renderer->startScene(ATMA::GLCamera{
        {  0.f,   0.f},
        {360.f, 360.f}
    });
    l_ctx.m_renderer->finishScene();
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
