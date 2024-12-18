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
        m_port = l_port;
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

        if(std::shared_ptr<Socket> l_client = m_listener->acceptConnection(); l_client != nullptr)
        {
            ATMA_ENGINE_INFO("Accepted client connection, giving id {}", m_nextId); 
            auto id = m_nextId;
            m_nextId++;
            m_clients[id] = l_client;
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
        ATMA_ENGINE_INFO("Setting client with id {} to block {}", l_client, l_block);
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

    bool NetworkHost::sendBytes(
        const ClientId &l_client,
        const std::span<unsigned char> &l_bytes,
        const size_t &l_size
    )
    {
        ATMA_ENGINE_INFO("Network Host is sending {0} bytes over port: {1}", l_size, m_port);
        return m_clients[l_client]->sendBytes(l_bytes, l_size);
    }

    bool NetworkHost::receiveBytes
    (
        const ClientId &l_client,
        std::span<unsigned char> &l_buffer,
        const size_t &l_size,
        size_t &l_receivedBytes
    )
    {
        std::span<unsigned char> buf{l_buffer};
        if(auto res = m_clients[l_client]->receiveBytes(buf, l_size, l_receivedBytes); res)
        {
            ATMA_ENGINE_INFO(
                "Network Host has received {0} bytes over port: {1}", l_receivedBytes, m_port
            );
            return true;
        }
        else
            return false;
    }

    bool NetworkHost::broadcastBytes(const std::span<unsigned char> &l_bytes, const size_t &l_size)
    {
        bool b{true};
        for(auto &l_client: m_clients)
        {
            if(!(l_client.second->sendBytes(l_bytes, l_size)))
                b = false;
        }
        return b;
    }

}