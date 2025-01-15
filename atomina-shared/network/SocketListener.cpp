#include "pch.hpp"
#include "SocketListener.hpp"
#ifdef _WINDOWS
#    include "platform/Win/network/SocketListenerWinImpl.hpp"
#    define __ATMAMAKESOCKETLISTENER(port) return std::make_shared<SocketListenerWinImpl>(port)
#elif __linux__
#    include "platform/Linux/network/SocketListenerUnixImpl.hpp"
#    define __ATMAMAKESOCKETLISTENER(port) return std::make_shared<SocketListenerUnixImpl>(port)
#endif

namespace ATMA
{

    SocketListener::SocketListener(const unsigned int &l_port): m_port(l_port) {}

    SocketListener::~SocketListener() {}

    std::shared_ptr<SocketListener> SocketListener::makeSocketListener(const unsigned short &l_port)
    {
        __ATMAMAKESOCKETLISTENER(l_port);
    }

}