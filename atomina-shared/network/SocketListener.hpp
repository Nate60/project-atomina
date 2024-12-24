#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "Socket.hpp"

namespace ATMA
{
    /**
     * Listening for active connections on a single port
     * using a local address
     */
    class SocketListener
    {
    public:
        // constructor specifying port
        SocketListener(const unsigned int &l_port);

        // deconstructor
        virtual ~SocketListener();

        /**
         * accepts a connection if there is a socket waiting
         * @return either a nullptr or a pointer to an active socket
         */
        virtual std::shared_ptr<Socket> acceptConnection() = 0;

        /**
         * factory function for socket listener
         * @param l_port port to open listener on
         * @return shared pointer to socket listener
         */
        static std::shared_ptr<SocketListener> makeSocketListener(const unsigned short &l_port);

        /**
         * convert socket info into string for logging
         * @return socket info as string
         */
        virtual const std::string toString() const = 0;

        const unsigned short m_port;
    };
}