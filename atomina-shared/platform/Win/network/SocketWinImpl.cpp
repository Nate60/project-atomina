#ifdef _WINDOWS
#    include "pch.hpp"
#    include "SocketWinImpl.hpp"

namespace ATMA
{

    SocketWinImpl::SocketWinImpl(const URL &l_url, const unsigned short &l_port): Socket(l_url, l_port)
    {
        ATMA_ENGINE_TRACE("Creating win sock");
        ZeroMemory(&m_hints, sizeof(m_hints));
        m_hints.ai_family = AF_UNSPEC;
        m_hints.ai_socktype = SOCK_STREAM;
        m_hints.ai_protocol = IPPROTO_TCP;

        bool addr = getaddrinfo(l_url.getIP().c_str(), std::to_string(l_port).c_str(), &m_hints, &m_addrinfo) == 0;
        if(!addr)
        {
            auto err = WSAGetLastError();
            ATMA_ENGINE_WARN("Socket failed to get address info: {0}", err);
            throw NetworkException("Socket unable to get address info" + std::to_string(err));
        }
        m_socket = socket(m_addrinfo->ai_family, m_addrinfo->ai_socktype, m_addrinfo->ai_protocol);

        if(m_socket == INVALID_SOCKET)
        {
            auto err = WSAGetLastError();
            freeaddrinfo(m_addrinfo);
            ATMA_ENGINE_WARN("Socket failed to create: {0}", err);
            throw NetworkException("Socket unable to be created" + std::to_string(err));
        }

        auto connected = connect(m_socket, m_addrinfo->ai_addr, static_cast<int>(m_addrinfo->ai_addrlen));

        if(connected == SOCKET_ERROR)
        {
            auto err = WSAGetLastError();
            closesocket(m_socket);
            m_socket = INVALID_SOCKET;
            freeaddrinfo(m_addrinfo);
            ATMA_ENGINE_WARN("Socket failed to connect: {0}", err);
            throw NetworkException("Socket unable to connect" + std::to_string(err));
        }

        freeaddrinfo(m_addrinfo);
        ATMA_ENGINE_TRACE("Finished creating win sock {}", m_socket);
    }

    SocketWinImpl::SocketWinImpl(SOCKET &&l_socket, const unsigned short &l_port):
        Socket(URL{""}, l_port),
        m_socket(l_socket)
    {
        ATMA_ENGINE_TRACE("move constructing win sock {}", m_socket);
    }

    SocketWinImpl::~SocketWinImpl()
    {
        ATMA_ENGINE_TRACE("Destroying Win Socket {}", m_socket);
        shutdown(m_socket, SD_SEND);
        closesocket(m_socket);
        m_socket = INVALID_SOCKET;
    }

    void SocketWinImpl::setBlocking(const bool &l_bool)
    {
        ATMA_ENGINE_TRACE("setting win socket blocking={}", l_bool);
        if(!l_bool)
        {
            unsigned long ul = 1;
            ioctlsocket(m_socket, FIONBIO, (unsigned long *)&ul);
        }
        else
        {
            unsigned long ul = 0;
            ioctlsocket(m_socket, FIONBIO, (unsigned long *)&ul);
        }
    }

    bool SocketWinImpl::sendBytes(const std::span<unsigned char> &l_buffer, const size_t &l_size)
    {
        if(l_size > l_buffer.size())
        {
            ATMA_ENGINE_WARN(
                "Socket refuses to send message with size({}) larger than buffer size({})", l_buffer.size(), l_size
            );
            return false;
        }
        ATMA_ENGINE_TRACE("win sock {} sending {} bytes", m_socket, l_size);
        int result = send(m_socket, reinterpret_cast<char *>(l_buffer.data()), l_size, 0);
        if(result == SOCKET_ERROR)
        {
            ATMA_ENGINE_WARN("Socket failed to send bytes: {0}", WSAGetLastError());
            closesocket(m_socket);
            return false;
        }
        return true;
    }

    const short
    SocketWinImpl::receiveBytes(std::span<unsigned char> &l_buffer, const size_t &l_size, size_t &l_receivedBytes)
    {
        int result = recv(m_socket, reinterpret_cast<char *>(l_buffer.data()), l_size, 0);
        if(result >= 0)
        {
            l_receivedBytes = result;
            return l_receivedBytes > 0;
        }
        else
        {
            int code = WSAGetLastError();
            switch(code)
            {
            case WSAEWOULDBLOCK: // retryable
                l_receivedBytes = 0;
                return 0;
            default:
                ATMA_ENGINE_WARN("Socket failed to received bytes: {}", code);
                return -1;
            }
        }
    }

    const std::string SocketWinImpl::toString() const
    {
        return std::to_string(m_socket);
    }

}

#else
#    error Windows implementation included in non-Windows target
#endif