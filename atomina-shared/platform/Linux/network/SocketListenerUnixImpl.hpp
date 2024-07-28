#ifdef __linux__
#    pragma once
#    include "pch.hpp"
#    include "core/api.hpp"
#    include <sys/types.h>
#    include <sys/socket.h>
#    include <netdb.h>
#    include <errno.h>
#    include "network/SocketListener.hpp"
#    include "SocketUnixImpl.hpp"
#    include "network/Socket.hpp"
#    include "util/Log.hpp"

namespace ATMA
{

    /**
     * Unix Implementation of network socket listener
     */
    class SocketListenerUnixImpl: public SocketListener
    {
    public:
        // constructor specifying port
        SocketListenerUnixImpl(const unsigned short &l_port);

        // deconstructor
        virtual ~SocketListenerUnixImpl();

        /**
         * opens port to active sockets
         * @return if the operation was successful
         */
        virtual bool startListening() override;

        /**
         * closes port so no more connections can be opened
         * @return if the operation was successful
         */
        virtual bool stopListening() override;

        /**
         * accepts a connection if there is a socket waiting
         * @return either a nullptr or a pointer to an active socket
         */
        virtual std::unique_ptr<Socket> acceptConnection() override;
    private:
        addrinfo *m_addrinfo, m_hints;
        int m_socket = 0;
        const unsigned int m_queueSize = 4;
    };

}

#else
#    error Linux implementation included in non-Linux target
#endif