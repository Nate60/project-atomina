#ifdef __linux__
#    include "pch.hpp"
#    include "SocketListenerUnixImpl.hpp"

namespace ATMA
{

    SocketListenerUnixImpl::SocketListenerUnixImpl(const unsigned short &l_port):
        SocketListener(l_port)
    {
    }

    SocketListenerUnixImpl::~SocketListenerUnixImpl() {}

    bool SocketListenerUnixImpl::startListening()
    {

        m_hints = {};
        m_hints.ai_family = AF_UNSPEC;
        m_hints.ai_socktype = SOCK_STREAM;
        m_hints.ai_flags = AI_PASSIVE;

        int status = 0;
        status = getaddrinfo(NULL, std::to_string(m_port).c_str(), &m_hints, &m_addrinfo);
        if(status != 0)
        {
            ATMA_ENGINE_WARN("Socket Listener failed to get address info: {0}", errno);
            freeaddrinfo(m_addrinfo);
            return false;
        }

        m_socket = socket(m_addrinfo->ai_family, m_addrinfo->ai_socktype, m_addrinfo->ai_protocol);

        int yes = 1;

        setsockopt(m_socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));

        status = bind(m_socket, m_addrinfo->ai_addr, m_addrinfo->ai_addrlen);
        if(status != 0)
        {
            ATMA_ENGINE_WARN("Socket Listener failed to bind to port: {0}", errno);
            freeaddrinfo(m_addrinfo);
            close(m_socket);
            return false;
        }

        status = listen(m_socket, m_queueSize);
        if(status != 0)
        {
            ATMA_ENGINE_WARN("Socket Listener failed to start listening: {0}", errno);
            close(m_socket);
            return false;
        }

        return true;
    }

    bool SocketListenerUnixImpl::stopListening()
    {
        freeaddrinfo(m_addrinfo);
        close(m_socket);
        return true;
    }

    std::shared_ptr<Socket> SocketListenerUnixImpl::acceptConnection()
    {
        std::shared_ptr<SocketUnixImpl> m_client = std::make_shared<SocketUnixImpl>();
        socklen_t addr_size;
        sockaddr_storage client_addr;
        m_client->m_socket = accept(m_socket, (sockaddr *)&client_addr, &addr_size);
        if(m_client->m_socket < 0)
        {
            ATMA_ENGINE_INFO("No connection was accepted");
            return nullptr;
        }

        return m_client;
    }

}

#else
#    error Linux implementation included in non-Linux target
#endif