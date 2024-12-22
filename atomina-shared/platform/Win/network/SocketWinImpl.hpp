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
        // default constructor
        SocketWinImpl();

        // deconstructor
        ~SocketWinImpl();

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
        virtual bool sendBytes(const std::span<unsigned char> &l_buffer, const size_t &l_size) override;

        /**
         * receives bytes from a remote server over the socket
         * @param l_buffer array view to store the received bytes
         * @param l_receivedBytes stores the amount of bytes actually received
         * @return if the operation was successful
         */
        virtual bool receiveBytes(std::span<unsigned char> &l_buffer, const size_t &l_size, size_t &l_receivedBytes) override;

        
        virtual std::string toString() override;

        friend class SocketListenerWinImpl;
        SOCKET m_socket = INVALID_SOCKET;
    private:
        addrinfo *m_addrinfo = NULL, m_hints;
    };

}

#else
#    error Windows implementation included in non-Windows target
#endif