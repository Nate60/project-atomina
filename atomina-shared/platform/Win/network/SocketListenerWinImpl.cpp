#ifdef _WINDOWS
#    include "pch.hpp"
#    include "SocketListenerWinImpl.hpp"

namespace ATMA
{

    SocketListenerWinImpl::SocketListenerWinImpl(const unsigned short &l_port):
        SocketListener(l_port)
    {

        ZeroMemory(&m_hints, sizeof(m_hints));
        m_hints.ai_family = AF_INET;
        m_hints.ai_socktype = SOCK_STREAM;
        m_hints.ai_protocol = IPPROTO_TCP;
        m_hints.ai_flags = AI_PASSIVE;

        int addr = getaddrinfo(NULL, std::to_string(l_port).c_str(), &m_hints, &m_addrinfo);
        if(addr != 0)
        {
            throw InitializationException("Socket Listener unable to get address info");
        }
    }

    SocketListenerWinImpl::~SocketListenerWinImpl() {}

    bool SocketListenerWinImpl::startListening()
    {
        m_listener =
            socket(m_addrinfo->ai_family, m_addrinfo->ai_socktype, m_addrinfo->ai_protocol);
        if(m_listener == INVALID_SOCKET)
        {
            ATMA_ENGINE_WARN("Socket Listener failed to create socket: {0}", WSAGetLastError());
            freeaddrinfo(m_addrinfo);
            return false;
        }

        auto addr = bind(m_listener, m_addrinfo->ai_addr, static_cast<int>(m_addrinfo->ai_addrlen));
        freeaddrinfo(m_addrinfo);
        if(addr == SOCKET_ERROR)
        {
            ATMA_ENGINE_WARN("Socket Listener failed to bind");
            closesocket(m_listener);
            return false;
        }

        if(listen(m_listener, SOMAXCONN) == SOCKET_ERROR)
        {
            ATMA_ENGINE_WARN("Socket Listener failed to listen");
            closesocket(m_listener);
            return false;
        }
        return true;
    }

    bool SocketListenerWinImpl::stopListening()
    {
        closesocket(m_listener);
        return true;
    }

    std::unique_ptr<Socket> SocketListenerWinImpl::acceptConnection()
    {
        std::unique_ptr<SocketWinImpl> m_client = std::make_unique<SocketWinImpl>();
        m_client->m_socket = INVALID_SOCKET;
        m_client->m_socket = accept(m_listener, NULL, NULL);
        if(m_client->m_socket == INVALID_SOCKET)
        {
            ATMA_ENGINE_INFO("No connection was accepted");
            closesocket(m_listener);
            return nullptr;
        }
        return m_client;
    }

}

#else
#    error Windows implementation included in non-Windows target
#endif