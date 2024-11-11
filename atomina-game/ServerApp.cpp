#ifdef ATMA_SERVER
#include "ServerApp.hpp"

ServerApp::ServerApp() {}

ServerApp::~ServerApp() {}

void ServerApp::setup(ATMA::ATMAContext &l_ctx) 
{
    active = true;
    ATMA_ENGINE_INFO("Running Server");
    l_ctx.addSystemType<SysFly>(ATMA::SysType(ATMA::System::COUNT));

}

void ServerApp::update(ATMA::ATMAContext &l_ctx)
{

    l_ctx.update();

}

void ServerApp::shutdown(ATMA::ATMAContext &l_ctx)
{
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