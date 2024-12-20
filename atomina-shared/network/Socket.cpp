#include "pch.hpp"
#include "Socket.hpp"
#ifdef _WINDOWS_
#    include "platform/Win/network/SocketWinImpl.hpp"
#    define __ATMAMAKESOCKET return std::make_shared<SocketWinImpl>();
#elif __linux__
#    include "platform/Linux/network/SocketUnixImpl.hpp"
#    define __ATMAMAKESOCKET return std::make_shared<SocketUnixImpl>();
#endif


namespace ATMA
{

    Socket::Socket() {}

    Socket::~Socket() {}

    std::shared_ptr<Socket> Socket::makeSocket()
    {
        __ATMAMAKESOCKET;
    }

}