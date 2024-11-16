#ifdef ATMA_SERVER
#include "ServerApp.hpp"

ServerApp::ServerApp() {}

ServerApp::~ServerApp() {}

void ServerApp::setup(ATMA::ATMAContext &l_ctx) 
{
    active = true;
    ATMA_ENGINE_INFO("Running Server");
    m_host.startListening();

}

void ServerApp::update(ATMA::ATMAContext &l_ctx)
{
    std::optional<unsigned int> conn_opt = std::nullopt;
    while(conn_opt == std::nullopt)
    {
        conn_opt = m_host.acceptConnections();
    }
    ATMA_ENGINE_INFO("User has connected");
    auto conn = conn_opt.value();
}

void ServerApp::shutdown(ATMA::ATMAContext &l_ctx)
{
    m_host.stopListening();
    m_host.purgeConnections();
    ATMA_ENGINE_INFO("Shutting down game");
}

std::unique_ptr<ATMA::Server> ATMA::CreateServer()
{
    #ifdef ATMA_OPENGL
    #error Cannot create server with OpenGL
    #endif
    return std::unique_ptr<ATMA::Server>{new ServerApp()};
}
#endif