#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "URL.hpp"

namespace ATMA
{

    /**
     * Used to connect and send bytes over a remote connection
     * using TCP Sockets
     */
    class Socket
    {
    public:
        // default constructor
        Socket();

        // deconstructor
        virtual ~Socket();

        /**
         * starts the connection to the host listener and waits for
         * it to accept the connection
         * @param l_addr remote URL of the host listener
         * @param l_port remote port of the host listener
         * @return if the operation was successful
         */
        virtual bool connectSocket(const URL &l_addr, const unsigned short &l_port) = 0;

        /**
         * ends the connection to the remote server
         * @return if the operation was succcessful
         */
        virtual bool closeSocket() = 0;

        /**
         * @brief toggles if the socket will wait for a message to be
         * received when sent
         * @param l_bool toggles blocking behaviour
         */
        virtual void setBlocking(const bool &l_bool) = 0;

        /**
         * sends bytes over the socket to the server, will block
         * if blocking is set to true (by default)
         * @param l_buffer array view of the bytes
         * @return if the operation was successful
         */
        virtual bool sendBytes(const std::span<unsigned char> &l_buffer, const size_t &l_size) = 0;

        /**
         * receives bytes from a remote server over the socket
         * @param l_buffer array view to store the received bytes
         * @param l_receivedBytes stores the amount of bytes actually received
         * @return if the operation was successful
         */
        virtual bool receiveBytes(std::span<unsigned char> &l_buffer, const size_t &l_size, size_t &l_receivedBytes) = 0;
    };

}