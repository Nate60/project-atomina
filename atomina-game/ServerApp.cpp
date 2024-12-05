#ifdef ATMA_SERVER
#    include "ServerApp.hpp"

ServerApp::ServerApp() {}

ServerApp::~ServerApp() {}

void ServerApp::setup(ATMA::ATMAContext &l_ctx)
{
    active = true;
    ATMA_ENGINE_INFO("Running Server");
    m_host.startListening(4734);
}

void ServerApp::update(ATMA::ATMAContext &l_ctx)
{
    while(conn_opt == std::nullopt)
    {
        conn_opt = m_host.acceptConnections();
        if(conn_opt != std::nullopt)
            ATMA_ENGINE_INFO("User has connected");
    }

    unsigned char buffer[ATMA::NETWORKMESSAGEBUFFERSIZE];
    size_t recvBytes;
    if(std::span<unsigned char> bufferView{buffer};
       m_host.receiveBytes(conn_opt.value(), bufferView, ATMA::NETWORKMESSAGEBUFFERSIZE, recvBytes))
    {
        ATMA::NetworkMessage nm = ATMA::NetworkSerde::deserialize(std::vector<unsigned char>{
            bufferView.begin(), bufferView.begin() + recvBytes});
        std::map<int, int> a;
        switch(static_cast<ATMA::NetworkMessageEnum>(nm.m_type))
        {
        case ATMA::NetworkMessageEnum::PORT_REQUEST:
            {
                std::pair<unsigned char, std::any> pair{
                    ATMA::NetworkMessageValueType(ATMA::NetworkMessageValueEnum::SHORT), (short)0};
                ATMA::Props p{{{"port", pair}}};
                ATMA_ENGINE_INFO("User has requested port data");
                ATMA::NetworkMessage resp{
                    ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::PORT_RESPONSE), p};
                std::vector<unsigned char> messageStream = ATMA::NetworkSerde::serialize(resp);
                m_host.sendBytes(
                    conn_opt.value(), std::span<unsigned char>{messageStream}, messageStream.size()

                );
            }
            break;
        default:
            ATMA_ENGINE_INFO("skipped network message type: {}", nm.m_type);
            break;
        }
    }
}

void ServerApp::shutdown(ATMA::ATMAContext &l_ctx)
{
    m_host.stopListening();
    m_host.purgeConnections();
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