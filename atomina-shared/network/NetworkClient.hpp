#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "URL.hpp"
#include "Socket.hpp"
#ifdef _WINDOWS_
#    include "socket/SocketWinImpl.hpp"
#elif __linux__
#    include "socket/SocketUnixImpl.hpp"
#endif

namespace ATMA
{
    class ATMA_API NetworkClient
    {
    public:
        // constructor specifying address and port of the host for connection
        NetworkClient(const URL &l_addr, const unsigned short &l_port);

        // default deconstructor
        virtual ~NetworkClient();

        NetworkClient(NetworkClient &&l_other) noexcept;

        /**
         * open connection on Client's port and address
         */
        void connect();

        /**
         * close Clients connection
         */
        void disconnect();

        /**
         * Sets whether or not the socket will block on waiting for a connection
         * @param l_bool toggles blocking
         */
        void setBlocking(const bool &l_bool);

        /**
         *  sends bytes over the socket uses std::array to enforce buffer is correct size
         *  to avoid buffer underflow
         *  @tparam size of the buffer
         *  @param l_bytes: array of bytes to send
         */
        template<size_t N>
        void sendBytes(const std::span<char, N> &l_bytes)
        {
            if(!(m_socket->sendBytes(l_bytes)))
                throw NetworkException(
                    "Unable to send bytes to remote address [" + m_addr.getIP() + ":"
                    + std::to_string(m_port) + "]"
                );
            else
                ATMA_ENGINE_INFO(
                    "Network Client sent {0} bytes over: {1}:{2}", N, m_addr.getIP(), m_port
                );
        }

        /**
         * receive bytes from socket. enforces buffer size so that way there is not buffer overflow
         * @tparam Size of the buffer
         * @param l_buffer: buffer to put bytes into
         * @param l_receivedBytes: length of received buffer
         */
        template<size_t N>
        void receiveBytes(std::span<char, N> &l_buffer, size_t &l_receivedBytes)
        {
            if(!(m_socket->receiveBytes(l_buffer, l_receivedBytes)))
                throw NetworkException("Unable to receive bytes");
            else
                ATMA_ENGINE_INFO(
                    "Network Client received {0} bytes over: {1}:{2}",
                    l_receivedBytes,
                    m_addr.getIP(),
                    m_port
                );
        }

        NetworkClient &operator=(NetworkClient &&l_other);
    protected:
        std::unique_ptr<Socket> m_socket;
        URL m_addr;
        unsigned short m_port;
    };

}