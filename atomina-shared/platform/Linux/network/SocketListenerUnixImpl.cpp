#ifdef __linux__
#    include "pch.hpp"
#    include "SocketListenerUnixImpl.hpp"

namespace ATMA
{

    SocketListenerUnixImpl::SocketListenerUnixImpl(const unsigned short &l_port): SocketListener(l_port)
    {
        ATMA_ENGINE_TRACE("Creating unix sock listener");
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
            throw NetworkException("Socket Listener unable to get address info " + std::to_string(errno));
        }

        m_socket = socket(m_addrinfo->ai_family, m_addrinfo->ai_socktype, m_addrinfo->ai_protocol);

        fcntl(m_socket, F_SETFL, O_NONBLOCK);

        int yes = 1;

        setsockopt(m_socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));

        status = bind(m_socket, m_addrinfo->ai_addr, m_addrinfo->ai_addrlen);
        if(status != 0)
        {
            ATMA_ENGINE_WARN("Socket Listener failed to bind to port: {0}", errno);
            freeaddrinfo(m_addrinfo);
            close(m_socket);
            throw NetworkException("Socket Listener unable to bind to port" + std::to_string(errno));
        }

        status = listen(m_socket, m_queueSize);
        if(status != 0)
        {
            ATMA_ENGINE_WARN("Socket Listener failed to start listening: {0}", errno);
            freeaddrinfo(m_addrinfo);
            close(m_socket);
            throw NetworkException("Socket Listener unable to start listening " + std::to_string(errno));
        }
        ATMA_ENGINE_TRACE("Finished creating unix sock listener {}", m_socket);
    }

    SocketListenerUnixImpl::~SocketListenerUnixImpl()
    {
        ATMA_ENGINE_TRACE("Destroying unix socket listener {}", m_socket);
        freeaddrinfo(m_addrinfo);
        close(m_socket);
    }

    std::shared_ptr<Socket> SocketListenerUnixImpl::acceptConnection()
    {
        socklen_t addr_size = sizeof(sockaddr_storage);
        sockaddr_storage client_addr;
        int socket = accept(m_socket, (sockaddr *)&client_addr, &addr_size);
        if(socket < 0)
        {
            return nullptr;
        }
        ATMA_ENGINE_TRACE("unix socket {} accepted from listener {}", socket, m_socket);
        return std::make_shared<SocketUnixImpl>(std::move(socket), m_port);
    }

    const std::string SocketListenerUnixImpl::toString() const
    {
        return std::to_string(m_socket);
    }

}

#else
#    error Linux implementation included in non-Linux target
#endif