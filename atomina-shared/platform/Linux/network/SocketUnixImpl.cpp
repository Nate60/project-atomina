#ifdef __linux__
#    include "pch.hpp"
#    include "SocketUnixImpl.hpp"

namespace ATMA
{

    SocketUnixImpl::SocketUnixImpl(): Socket() {}

    SocketUnixImpl::~SocketUnixImpl() {}

    bool SocketUnixImpl::connectSocket(const URL &l_addr, const unsigned short &l_port)
    {

        m_hints = {};
        m_hints.ai_family = AF_UNSPEC;
        m_hints.ai_socktype = SOCK_STREAM;

        int status = 0;
        status = getaddrinfo(
            l_addr.getIP().c_str(), std::to_string(l_port).c_str(), &m_hints, &m_addrinfo
        );
        if(status != 0)
        {
            ATMA_ENGINE_WARN("Socket Listener failed to get address info: {0}", errno);
            freeaddrinfo(m_addrinfo);
            return false;
        }

        m_socket = socket(m_addrinfo->ai_family, m_addrinfo->ai_socktype, m_addrinfo->ai_protocol);
        if(m_socket <= 0)
        {
            ATMA_ENGINE_WARN("Socket failed to be created: {0}", errno);
            freeaddrinfo(m_addrinfo);
            close(m_socket);
            return false;
        }

        m_connection = connect(m_socket, m_addrinfo->ai_addr, m_addrinfo->ai_addrlen);
        if(m_connection < 0)
        {
            ATMA_ENGINE_WARN("Socket failed to connect: {0}", errno);
            freeaddrinfo(m_addrinfo);
            close(m_socket);
            return false;
        }
        freeaddrinfo(m_addrinfo);

        return true;
    }

    bool SocketUnixImpl::closeSocket()
    {
        close(m_socket);
        return true;
    }

    void SocketUnixImpl::setBlocking(const bool &l_bool)
    {

        if(!l_bool)
        {
            fcntl(m_socket, F_SETFL, O_NONBLOCK);
        }
        else
        {
            fcntl(m_socket, F_SETFL, ~O_NONBLOCK);
        }
    }

    bool SocketUnixImpl::sendBytes(const std::span<char> &l_buffer)
    {
        int result = send(m_socket, l_buffer.data(), l_buffer.size(), 0);
        if(result < 0)
        {
            ATMA_ENGINE_WARN("Socket failed to send bytes: {0}", errno);
            close(m_socket);
            return false;
        }
        return true;
    }

    bool SocketUnixImpl::receiveBytes(std::span<char> &l_buffer, size_t &l_receivedBytes)
    {
        int result = read(m_socket, l_buffer.data(), l_buffer.size());
        if(result >= 0)
        {
            l_receivedBytes = result;
        }
        else
        {
            ATMA_ENGINE_WARN("Socket failed to received bytes: {0}", errno);
            return false;
        }
        return true;
    }

}

#else
#    error Linux implementation included in non-Linux target
#endif