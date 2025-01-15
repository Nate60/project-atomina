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
        addrinfo *m_addrinfo, m_hints;
        int m_socket = 0;
        const unsigned int m_queueSize = 4;
    };

}

#else
#    error Linux implementation included in non-Linux target
#endif