#ifdef _WINDOWS
#    pragma once
#    include "pch.hpp"
#    include "core/api.hpp"
#    include <winsock2.h>
#    include <ws2tcpip.h>
#    include <iphlpapi.h>
#    include <stdio.h>
#    include "network/Socket.hpp"
#    include "util/AtominaException.hpp"
#    include "util/Log.hpp"

#    pragma comment(lib, "Ws2_32.lib")

namespace ATMA
{
    class SocketListenerWinImpl;

    /**
     * Windows Specific implementation of the socket
     */
    class SocketWinImpl: public Socket
    {
    public:
        // constructor to acquire socket
        SocketWinImpl(const URL &l_addr, const unsigned short &l_port);

        // constructor to pass in native socket
        SocketWinImpl(SOCKET &&l_socket, const unsigned short &l_port);

        // deconstructor
        ~SocketWinImpl();

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

        friend class SocketListenerWinImpl;
    private:
        SOCKET m_socket;
        addrinfo *m_addrinfo = NULL, m_hints;
    };

}

#else
#    error Windows implementation included in non-Windows target
#endif