#pragma once
// conversion to template types causing warning
#include "AtominaTest.hpp"

class NetworkFixture: public ::testing::Test
{
protected:
    std::shared_ptr<ATMA::Socket> socket;
    std::shared_ptr<ATMA::SocketListener> listener;

    const unsigned short m_port = 8899;

    ATMA::URL m_address{"127.0.0.1"};

    void SetUp() override
    {
#ifdef _WINDOWS
        socket = std::make_shared<ATMA::SocketWinImpl>();
        listener = std::make_shared<ATMA::SocketListenerWinImpl>(m_port);
#else
        socket = std::make_shared<ATMA::SocketUnixImpl>();
        listener = std::make_shared<ATMA::SocketListenerUnixImpl>(m_port);
#endif
        socket->setBlocking(false);
    }

    void TearDown() override
    {
        if(socket != nullptr)
        {
            socket->closeSocket();
        }

        if(listener != nullptr)
        {
            listener->stopListening();
        }
    }
};

class NetworkClientHostFixture: public ::testing::Test
{
protected:
    const unsigned short m_port = 8899;
    ATMA::URL m_address{"127.0.0.1"};

    ATMA::NetworkClient m_client{};
    ATMA::NetworkHost m_host{};

    void SetUp() override
    {
        m_client = {};
        m_host = {};
        m_client.setBlocking(false);
    }

    void TearDown() override
    {
        ATMA_ENGINE_TRACE("starting tear down");
        m_client.disconnect();
        ATMA_ENGINE_TRACE("disconnected client");
        m_host.purgeConnections();
        ATMA_ENGINE_TRACE("purged host connections");
        m_host.stopListening();
        ATMA_ENGINE_TRACE("stopped host from listening");
        ATMA_ENGINE_TRACE("stopped teardown...");
    }
};