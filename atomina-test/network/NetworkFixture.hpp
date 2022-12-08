#pragma once
#include "AtominaTest.hpp"

/**
 * Test fixture for setting up networking sockets
 */
class NetworkFixture: public ::testing::Test
{
public:
    unsigned short port = 22000;
    sf::IpAddress addr = sf::IpAddress::LocalHost;
    ATMA::NetworkHost l_host{port};
    ATMA::NetworkClient l_client{addr, port};
    ATMA::NetworkClient l_client2{addr, port};
protected:
    /**
     * Creates all sockets
     */
    void SetUp() override
    {
        l_host = ATMA::NetworkHost(port);
        l_client = ATMA::NetworkClient(addr, port);
        l_client2 = ATMA::NetworkClient(addr, port);
    }

    /**
     * Closes all sockets
     */
    void TearDown() override
    {
        l_host.stopListening();
        l_client.disconnect();
        l_client2.disconnect();
        l_host.purgeConnections();
    }
};