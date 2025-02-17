#ifdef _WINDOWS
#    pragma once
#    include "pch.hpp"
#    include "core/api.hpp"
#    include <winsock2.h>
#    include <ws2tcpip.h>
#    include <iphlpapi.h>
#    include <stdio.h>
#    include "network/Socket.hpp"
#    include "network/SocketListener.hpp"
#    include "platform/Win/network/SocketWinImpl.hpp"
#    include "util/AtominaException.hpp"
#    include "util/Log.hpp"

#    pragma comment(lib, "Ws2_32.lib")

namespace ATMA
{

    /**
     * Windows implementation of network socket listener
     */
    class SocketListenerWinImpl: public SocketListener
    {
    public:
        // constructor specifying port
        SocketListenerWinImpl(const unsigned short &l_port);

        // deconstructor
        virtual ~SocketListenerWinImpl();

        /**
         * accepts a connection if there is a socket waiting
         * @return either a nullptr or a pointer to an active socket
         */
        virtual std::shared_ptr<Socket> acceptConnection() override;

        /**
         * convert socket info into string for logging
         * @return socket info as string
         */
        virtual const std::string toString() const override;
    private:
        addrinfo *m_addrinfo = NULL, m_hints;
        SOCKET m_listener = INVALID_SOCKET;
    };

}

#else
#    error Windows implementation included in non-Windows target
#endif