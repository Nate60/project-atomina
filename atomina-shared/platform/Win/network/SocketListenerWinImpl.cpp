#ifdef _WINDOWS
#    include "pch.hpp"
#    include "SocketListenerWinImpl.hpp"

namespace ATMA
{

    SocketListenerWinImpl::SocketListenerWinImpl(const unsigned short &l_port): SocketListener(l_port)
    {
        ATMA_ENGINE_TRACE("Creating win sock listener");
        ZeroMemory(&m_hints, sizeof(m_hints));
        m_hints.ai_family = AF_INET;
        m_hints.ai_socktype = SOCK_STREAM;
        m_hints.ai_protocol = IPPROTO_TCP;
        m_hints.ai_flags = AI_PASSIVE;

        int addr = getaddrinfo(NULL, std::to_string(l_port).c_str(), &m_hints, &m_addrinfo);
        if(addr != 0)
        {
            throw NetworkException("Socket Listener unable to get address info");
        }
        m_listener = socket(m_addrinfo->ai_family, m_addrinfo->ai_socktype, m_addrinfo->ai_protocol);
        if(m_listener == INVALID_SOCKET)
        {
            auto err = WSAGetLastError();
            ATMA_ENGINE_WARN("Socket Listener failed to create socket: {0}", err);
            freeaddrinfo(m_addrinfo);
            throw NetworkException("Socket Listener unable to create socket " + std::to_string(err));
        }

        unsigned long ul = 1;
        ioctlsocket(m_listener, FIONBIO, (unsigned long *)&ul);

        auto socketBind = bind(m_listener, m_addrinfo->ai_addr, static_cast<int>(m_addrinfo->ai_addrlen));
        freeaddrinfo(m_addrinfo);
        if(socketBind == SOCKET_ERROR)
        {
            auto err = WSAGetLastError();
            ATMA_ENGINE_WARN("Socket Listener failed to bind {}", err);
            closesocket(m_listener);
            freeaddrinfo(m_addrinfo);
            throw NetworkException("Socket Listener unable to bind socket " + std::to_string(err));
        }

        if(listen(m_listener, SOMAXCONN) == SOCKET_ERROR)
        {
            auto err = WSAGetLastError();
            ATMA_ENGINE_WARN("Socket Listener failed to listen {}", err);
            closesocket(m_listener);
            throw NetworkException("Socket Listener unable to listen " + std::to_string(err));
        }
        ATMA_ENGINE_TRACE("Finished creating win sock listener {}", m_listener);
    }

    SocketListenerWinImpl::~SocketListenerWinImpl()
    {
        ATMA_ENGINE_TRACE("Destroying win socket listener {}", m_listener);
        closesocket(m_listener);
    }

    std::shared_ptr<Socket> SocketListenerWinImpl::acceptConnection()
    {
        SOCKET socket = accept(m_listener, NULL, NULL);
        if(socket == INVALID_SOCKET)
        {
            return nullptr;
        }
        ATMA_ENGINE_TRACE("win socket {} accepted from listener {}", socket, m_listener);
        return std::make_shared<SocketWinImpl>(std::move(socket), m_port);
    }

    const std::string SocketListenerWinImpl::toString() const
    {
        return std::to_string(m_listener);
    }

}

#else
#    error Windows implementation included in non-Windows target
#endif