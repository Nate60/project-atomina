#pragma once
#include "../AtominaTest.hpp"
#include "network/NetworkClient.hpp"
#include <SFML/Network/IpAddress.hpp>

class NetworkFixture : public ::testing::Test
{
public:
    unsigned short port = 22000;
    sf::IpAddress addr = sf::IpAddress::LocalHost;
    ATMA::NetworkHost l_host{ port };
    ATMA::NetworkClient l_client{ addr, port };
    ATMA::NetworkClient l_client2{addr, port};

protected:
    void SetUp() override
    {
        l_host = ATMA::NetworkHost(port);
        l_client = ATMA::NetworkClient(addr, port);
        l_client2 = ATMA::NetworkClient(addr, port);
    }

    void TearDown() override
    {
        l_host.stopListening();
        l_client.disconnect();
        l_client.disconnect();
        l_host.purgeConnections();
    }

};