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
    protected:
        // protected constructor so only factory function can make it
        Socket(const URL &l_addr, const unsigned short &l_port);
    public:
        // deconstructor
        virtual ~Socket();

        /**
         * @brief toggles if the socket will wait for a message to be
         * received when sent
         * @param l_bool toggles blocking behaviour
         */
        virtual void setBlocking(const bool &l_bool) = 0;

        /**
         * sends bytes over the socket to the server, will block
         * if blocking is set to true (by default) will fail if the buffer size is smaller
         * than size given
         * @param l_buffer array view of the bytes
         * @return if the operation was successful
         */
        virtual bool sendBytes(const std::span<unsigned char> &l_buffer, const size_t &l_size) = 0;

        /**
         * receives bytes from a remote server over the socket
         * @param l_buffer array view to store the received bytes
         * @param l_receivedBytes stores the amount of bytes actually received
         * @return 0 if no message received, 1 if message received, and -1 if an error occured
         */
        virtual const short
        receiveBytes(std::span<unsigned char> &l_buffer, const size_t &l_size, size_t &l_receivedBytes) = 0;

        /**
         * convert socket info into string for logging
         * @return socket info as string
         */
        virtual const std::string toString() const = 0;

        /**
         * factory function for creating sockets
         * @param l_url endpoint to connect to
         * @param l_port port to connect to
         * @return shared pointer to socket
         */
        static std::shared_ptr<Socket> makeSocket(const URL &l_url, const unsigned short &l_port);

        const URL m_url;
        const unsigned short m_port;
    };

    /**
     * socket logging formatting func
     * @param os output stream to pipe into
     * @param sock socket object to log
     */
    inline std::ostream &operator<<(std::ostream &os, std::shared_ptr<Socket> sock)
    {
        return os << sock->toString();
    }

}