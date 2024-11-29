#include "pch.hpp"
#include "NetworkHost.hpp"

namespace ATMA
{

    NetworkHost::NetworkHost()
    {
    }

    NetworkHost::NetworkHost(NetworkHost &&l_other) noexcept: m_port(l_other.m_port)
    {

        m_listener = std::move(l_other.m_listener);
        m_clients = std::move(l_other.m_clients);
        m_nextId = l_other.m_nextId;
    }

    NetworkHost::~NetworkHost() {}

    bool NetworkHost::startListening(const unsigned short &l_port)
    {
#ifdef _WINDOWS_
        m_listener = std::make_unique<SocketListenerWinImpl>(l_port);
#elif __linux__
        m_listener = std::make_unique<SocketListenerUnixImpl>(l_port);
#endif
        return m_listener->startListening();
    }

    void NetworkHost::stopListening()
    {
        m_listener->stopListening();
    }

    std::optional<NetworkHost::ClientId> NetworkHost::acceptConnections()
    {

        // need to create a pointer to new object on heap so that it can live outside the function
        // scope

        if(std::unique_ptr<Socket> l_client = m_listener->acceptConnection(); l_client != nullptr)
        {
            auto id = m_nextId;
            m_nextId++;
            m_clients[id] = std::move(l_client);
            return id;
        }
        else
        {
            return std::nullopt;
        }
    }

    void NetworkHost::closeConnection(const ClientId &l_client)
    {

        m_clients[l_client]->closeSocket();
        m_clients.erase(l_client);
    }

    void NetworkHost::purgeConnections()
    {
        ATMA_ENGINE_INFO("Host is purging connections");
        for(auto &l_client: m_clients)
        {
            l_client.second->closeSocket();
        }
        m_clients.clear();
        m_nextId = 0;
    }

    void NetworkHost::setBlocking(const ClientId &l_client, const bool &l_block)
    {
        m_clients[l_client]->setBlocking(l_block);
    }

    NetworkHost &NetworkHost::operator=(NetworkHost &&l_other)
    {
        m_port = l_other.m_port;
        m_listener = std::move(l_other.m_listener);
        m_clients = std::move(l_other.m_clients);
        m_nextId = l_other.m_nextId;
        return *this;
    }

}