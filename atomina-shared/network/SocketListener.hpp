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
        SocketListener(const unsigned short &l_port);

        // deconstructor
        virtual ~SocketListener();

        /**
         * opens port to active sockets
         * @return if the operation was successful
         */
        virtual bool startListening() = 0;

        /**
         * closes port so no more connections can be opened
         * @return if the operation was successful
         */
        virtual bool stopListening() = 0;

        /**
         * accepts a connection if there is a socket waiting
         * @return either a nullptr or a pointer to an active socket
         */
        virtual std::shared_ptr<Socket> acceptConnection() = 0;

        static std::shared_ptr<SocketListener> makeSocketListener(const unsigned short &l_port);

        const unsigned short m_port;
    };
}