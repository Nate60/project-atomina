#include "pch.hpp"
#include "NetworkClient.hpp"

namespace ATMA
{
    NetworkClient::NetworkClient()
    {
#ifdef _WINDOWS_
        m_socket = std::make_unique<SocketWinImpl>();
#elif __linux__
        m_socket = std::make_unique<SocketUnixImpl>();
#endif
    }

    NetworkClient::NetworkClient(NetworkClient &&l_other) noexcept
    {
        m_addr = l_other.m_addr;
        m_port = l_other.m_port;
        m_socket = std::move(l_other.m_socket);
    }

    NetworkClient::~NetworkClient() {}

    void NetworkClient::connect(const URL &l_addr, const unsigned short &l_port)
    {
        m_addr = l_addr;
        m_port = l_port;
        ATMA_ENGINE_INFO("Network Client created for IP: {0} : {1}", m_addr.getIP(), m_port);
        if(!(m_socket->connectSocket(m_addr, m_port)))
            throw NetworkException(
                "Unable to connect to remote address [" + m_addr.getIP() + ":"
                + std::to_string(m_port) + "]"
            );
        else
            ATMA_ENGINE_INFO("Network Client connected to IP: {0} : {1}", m_addr.getIP(), m_port);
    }

    void NetworkClient::disconnect()
    {
        m_socket->closeSocket();
    }

    void NetworkClient::setBlocking(const bool &l_bool)
    {
        m_socket->setBlocking(l_bool);
    }

    NetworkClient &NetworkClient::operator=(NetworkClient &&l_other)
    {
        m_addr = l_other.m_addr;
        m_port = l_other.m_port;
        m_socket = std::move(l_other.m_socket);
        return *this;
    }

}