#ifdef ATMA_SERVER
#    include "ServerApp.hpp"
#    include "OAS/AttrConnection.hpp"
#    include "OAS/SysConnection.hpp"
#    include "state/ServerState.hpp"

ServerApp::ServerApp() {}

ServerApp::~ServerApp() {}

void ServerApp::setup(ATMA::ATMAContext &l_ctx)
{
    active = true;
    ATMA_ENGINE_INFO("Running Server");
    l_ctx.m_attrMan->registerAttributeType<AttrConnection>(GameAttributeType(GameAttributeEnum::CONNECTION));
    l_ctx.m_sysMan->addSystemType<SysConnection>(GameSystemType(GameSystemEnum::CONNECTION));
    auto netSys = l_ctx.m_sysMan->getSystem<SysConnection>(GameSystemType(GameSystemEnum::CONNECTION));
    l_ctx.m_netMan->addMessageListener(ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::CONNECTION_STARTED), netSys);
    l_ctx.m_netMan->addMessageListener(ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::PORT_REQUEST), netSys);
    l_ctx.m_netMan->addMessageListener(ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::STATE_CHANGE), netSys);
    l_ctx.m_netMan->addMessageListener(GameNetMessageType(GameNetMessageEnum::PLAYER_CHOICE), netSys);
    std::shared_ptr<ServerState> server = std::make_shared<ServerState>();
    l_ctx.m_eventMan->addObjectEventListener(ATMA::ObjectEventType(ATMA::ObjectEvent::Network), server);
    l_ctx.m_stateMan->addState(GameStateType(GameStateEnum::PLAYSTATE), server);
    l_ctx.m_netMan->startHosting(4734);
}

void ServerApp::update(ATMA::ATMAContext &l_ctx, const long long &l_dt)
{
    l_ctx.m_sysMan->update(l_ctx, l_dt);
}

void ServerApp::shutdown(ATMA::ATMAContext &l_ctx)
{
    l_ctx.m_netMan->stopHosting();
    ATMA_ENGINE_INFO("Shutting down game");
}

std::unique_ptr<ATMA::Server> ATMA::CreateServer()
{
#    ifdef ATMA_OPENGL
#        error Cannot create server with OpenGL
#    endif
    return std::unique_ptr<ATMA::Server>{new ServerApp()};
}
#endif
