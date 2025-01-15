#include "pch.hpp"
#include "Socket.hpp"
#ifdef _WINDOWS
#    include "platform/Win/network/SocketWinImpl.hpp"
#    define __ATMAMAKESOCKET(url, port) return std::make_shared<SocketWinImpl>(url, port)
#elif __linux__
#    include "platform/Linux/network/SocketUnixImpl.hpp"
#    define __ATMAMAKESOCKET(url, port) return std::make_shared<SocketUnixImpl>(url, port)
#endif

namespace ATMA
{

    Socket::Socket(const URL &l_url, const unsigned short &l_port): m_url(l_url), m_port(l_port) {}

    Socket::~Socket() {}

    std::shared_ptr<Socket> Socket::makeSocket(const URL &l_url, const unsigned short &l_port)
    {
        __ATMAMAKESOCKET(l_url, l_port);
    }
}