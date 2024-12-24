#ifdef __linux__
#    include "pch.hpp"
#    include "SocketUnixImpl.hpp"

namespace ATMA
{

    SocketUnixImpl::SocketUnixImpl(const URL &l_addr, const unsigned short &l_port): Socket(l_addr, l_port)
    {
        ATMA_ENGINE_TRACE("Creating unix sock");
        m_hints = {};
        m_hints.ai_family = AF_UNSPEC;
        m_hints.ai_socktype = SOCK_STREAM;

        int status = 0;
        status = getaddrinfo(l_addr.getIP().c_str(), std::to_string(l_port).c_str(), &m_hints, &m_addrinfo);
        if(status != 0)
        {
            ATMA_ENGINE_WARN("Socket failed to get address info: {0}", errno);
            freeaddrinfo(m_addrinfo);
            throw NetworkException("Socket unable to get address info " + std::to_string(errno));
        }

        m_socket = socket(m_addrinfo->ai_family, m_addrinfo->ai_socktype, m_addrinfo->ai_protocol);
        if(m_socket <= 0)
        {
            ATMA_ENGINE_WARN("Socket failed to be created: {0}", errno);
            freeaddrinfo(m_addrinfo);
            close(m_socket);
            throw NetworkException("Socket unable to be created " + std::to_string(errno));
        }

        m_connection = connect(m_socket, m_addrinfo->ai_addr, m_addrinfo->ai_addrlen);
        if(m_connection < 0)
        {
            ATMA_ENGINE_WARN("Socket failed to connect: {0}", errno);
            freeaddrinfo(m_addrinfo);
            close(m_socket);
            throw NetworkException("Socket unable to connect" + std::to_string(errno));
        }

        freeaddrinfo(m_addrinfo);
        ATMA_ENGINE_TRACE("Finished creating unix sock {}", m_socket);
    }

    SocketUnixImpl::SocketUnixImpl(int &&l_socket, const unsigned short &l_port):
        Socket(URL{""}, l_port),
        m_socket(l_socket)
    {
        ATMA_ENGINE_TRACE("move constructing unix sock {}", m_socket);
    }

    SocketUnixImpl::~SocketUnixImpl()
    {
        ATMA_ENGINE_TRACE("Destroying unix socket {}", m_socket);
        // TODO: shutdown
        close(m_socket);
    }

    void SocketUnixImpl::setBlocking(const bool &l_bool)
    {
        ATMA_ENGINE_TRACE("setting unix socket blocking={}", l_bool);
        if(!l_bool)
        {
            fcntl(m_socket, F_SETFL, O_NONBLOCK);
        }
        else
        {
            fcntl(m_socket, F_SETFL, ~O_NONBLOCK);
        }
    }

    bool SocketUnixImpl::sendBytes(const std::span<unsigned char> &l_buffer, const size_t &l_size)
    {
        if(l_size > l_buffer.size())
        {
            ATMA_ENGINE_WARN(
                "Socket refuses to send message with size({}) larger than buffer size({})", l_buffer.size(), l_size
            );
            return false;
        }
        ATMA_ENGINE_TRACE("unix sock {} sending {} bytes", m_socket, l_size);
        int result = send(m_socket, reinterpret_cast<const char *>(l_buffer.data()), l_size, 0);
        if(result < 0)
        {
            ATMA_ENGINE_WARN("Socket failed to send bytes: {0}", errno);
            close(m_socket);
            return false;
        }
        return true;
    }

    const short
    SocketUnixImpl::receiveBytes(std::span<unsigned char> &l_buffer, const size_t &l_size, size_t &l_receivedBytes)
    {
        int result = read(m_socket, reinterpret_cast<char *>(l_buffer.data()), l_size);
        if(result >= 0)
        {
            l_receivedBytes = result;
            return l_receivedBytes > 0;
        }
        else
        {
            int code = errno;
            switch(code)
            {
            case 11: // retry-able
                l_receivedBytes = 0;
                return 0;
            default:
                ATMA_ENGINE_WARN("Socket failed to received bytes: {}", code);
                return -1;
            }
        }
    }

    const std::string SocketUnixImpl::toString() const
    {
        return std::to_string(m_socket);
    }

}

#else
#    error Linux implementation included in non-Linux target
#endif