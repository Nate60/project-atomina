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

    /**
     * Unix implementation of network socket
     */
    class SocketUnixImpl: public Socket
    {
    public:
        // constructor to acquire socket
        SocketUnixImpl(const URL &l_addr, const unsigned short &l_port);

        // constructor to pass in native socket
        SocketUnixImpl(int &&l_socket, const unsigned short &l_port);

        // default deconstructor
        virtual ~SocketUnixImpl();

        /**
         * @brief toggles if the socket will wait for a message to be
         * received when sent
         * @param l_bool toggles blocking behaviour
         */
        virtual void setBlocking(const bool &l_bool) override;

        /**
         * sends bytes over the socket to the server, will block
         * if blocking is set to true (by default) will fail if the buffer size is smaller
         * than size given
         * @param l_buffer array view of the bytes
         * @return if the operation was successful
         */
        virtual bool sendBytes(const std::span<unsigned char> &l_buffer, const size_t &l_size) override;

        /**
         * receives bytes from a remote server over the socket
         * @param l_buffer array view to store the received bytes
         * @param l_receivedBytes stores the amount of bytes actually received
         * @return 0 if no message received, 1 if message received, and -1 if an error occured
         */
        virtual const short
        receiveBytes(std::span<unsigned char> &l_buffer, const size_t &l_size, size_t &l_receivedBytes) override;

        /**
         * convert socket info into string for logging
         * @return socket info as string
         */
        virtual const std::string toString() const override;

        friend class SocketListenerUnixImpl;
    private:
        int m_socket = 0, m_connection = 0;
        addrinfo *m_addrinfo, m_hints;
    };

}

#else
#    error Linux implementation included in non-Linux target
#endif