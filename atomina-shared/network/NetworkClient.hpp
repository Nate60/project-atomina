#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "URL.hpp"
#include "Socket.hpp"
#ifdef _WINDOWS_
#    include "platform/Win/network/SocketWinImpl.hpp"
#elif __linux__
#    include "platform/Linux/network/SocketUnixImpl.hpp"
#endif

namespace ATMA
{
    /**
     * TCP Client for connecting to hosts, can only connect to one
     * host
     */
    class NetworkClient
    {
    public:
        // constructor specifying address and port of the host for connection
        NetworkClient();

        // default deconstructor
        virtual ~NetworkClient();

        NetworkClient(NetworkClient &&l_other) noexcept;

        /**
         * open connection on Client's port and address
         */
        void connect(const URL &l_addr, const unsigned short &l_port);

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
        void sendBytes(const std::span<unsigned char> &l_bytes, const size_t &l_size);

        /**
         * receive bytes from socket. enforces buffer size so that way there is not buffer overflow
         * @tparam Size of the buffer
         * @param l_buffer: buffer to put bytes into
         * @param l_receivedBytes: length of received buffer
         */
        void receiveBytes(
            std::span<unsigned char> &l_buffer,
            const size_t &l_size,
            size_t &l_receivedBytes
        );


        NetworkClient &operator=(NetworkClient &&l_other);
    protected:
        std::unique_ptr<Socket> m_socket;
        URL m_addr;
        unsigned short m_port;
    };

}