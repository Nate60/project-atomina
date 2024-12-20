#include "pch.hpp"
#include "SocketListener.hpp"
#ifdef _WINDOWS_
#    include "platform/Win/network/SocketListenerWinImpl.hpp"
#    define __ATMAMAKESOCKETLISTENER(port) return std::make_unique<SocketListenerWinImpl>(port);
#elif __linux__
#    include "platform/Linux/network/SocketListenerUnixImpl.hpp"
#    define __ATMAMAKESOCKETLISTENER(port) return std::make_unique<SocketListenerUnixImpl>(port);
#endif

namespace ATMA
{

    SocketListener::SocketListener(const unsigned short &l_port): m_port(l_port) {}

    SocketListener::~SocketListener() {}

    std::shared_ptr<SocketListener> SocketListener::makeSocketListener(const unsigned short &l_port)
    {
        __ATMAMAKESOCKETLISTENER(l_port);
    }

}