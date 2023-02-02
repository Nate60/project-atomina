#ifdef __linux__
#    pragma once
#    include "pch.hpp"
#    include <stdio.h>
#    include <stdlib.h>
#    include <sys/types.h>
#    include <sys/socket.h>
#    include <netdb.h>
#    include <fcntl.h>
#    include "core/api.hpp"
#    include "network/URL.hpp"
#    include "network/Socket.hpp"
#    include "util/Log.hpp"

namespace ATMA
{
    class SocketListenerUnixImpl;

    class ATMA_API SocketUnixImpl: public Socket
    {
    public:
        SocketUnixImpl();

        ~SocketUnixImpl();

        /**
         * starts the connection to the host listener and waits for
         * it to accept the connection
         * @param l_addr remote URL of the host listener
         * @param l_port remote port of the host listener
         * @return if the operation was successful
         */
        virtual bool connectSocket(const URL &l_addr, const unsigned short &l_port) override;

        /**
         * ends the connection to the remote server
         * @return if the operation was succcessful
         */
        virtual bool closeSocket() override;

        /**
         * @brief toggles if the socket will wait for a message to be
         * received when sent
         * @param l_bool toggles blocking behaviour
         */
        virtual void setBlocking(const bool &l_bool) override;

        /**
         * sends bytes over the socket to the server, will block
         * if blocking is set to true (by default)
         * @param l_buffer array view of the bytes
         * @return if the operation was successful
         */
        virtual bool sendBytes(const std::span<char> &l_buffer) override;

        /**
         * receives bytes from a remote server over the socket
         * @param l_buffer array view to store the received bytes
         * @param l_receivedBytes stores the amount of bytes actually received
         * @return if the operation was successful
         */
        virtual bool receiveBytes(std::span<char> &l_buffer, size_t &l_receivedBytes) override;

        friend class SocketListenerUnixImpl;
    private:
        int m_socket = 0, m_connection = 0;
        addrinfo *m_addrinfo, m_hints;
    };

}

#else
#    error Linux implementation included in non-linux target
#endif