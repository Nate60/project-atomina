#include "NetworkTestSuite.hpp"

/**
 * Network client should be able to connect to an
 * available network host
 */
TEST_F(NetworkFixture, ClientCanConnect)
{
    l_host.startListening();
    l_client.connect();
    unsigned int id = l_host.acceptConnections().value_or(100u);
    EXPECT_EQ(id, 0u);
}

/**
 * Network client should be able to receive messages from a host
 * the client is connected to
 */
TEST_F(NetworkFixture, ClientCanReceive)
{
    const size_t len = 3;
    l_host.startListening();
    l_client.connect();
    unsigned int id = l_host.acceptConnections().value_or(100u);
    const std::array<std::byte, len> bytes = {std::byte{0x60}, std::byte{0x61}, std::byte{0x62}};
    l_host.broadcastBytes<len>(bytes);
    std::array<std::byte, len> msg;
    size_t receivedBytesLen = 0;
    l_client.receiveBytes<len>(msg, receivedBytesLen);

    EXPECT_EQ(len, receivedBytesLen);
    for(int i = 0; i < len; i++)
        EXPECT_EQ(std::to_integer<int>(msg[i]), std::to_integer<int>(bytes[i]));
}

/**
 * Network host should be able to receive messages from anyone of
 * its connected network clients
 */
TEST_F(NetworkFixture, ClientCanSend)
{
    const size_t len = 3;
    l_host.startListening();
    l_client.connect();
    unsigned int id = l_host.acceptConnections().value_or(100u);
    const std::array<std::byte, len> bytes = {std::byte{0x60}, std::byte{0x61}, std::byte{0x62}};
    l_client.sendBytes<len>(bytes);
    std::array<std::byte, len> msg;
    size_t receivedBytesLen = 0;
    l_host.receiveBytes<len>(id, msg, receivedBytesLen);

    EXPECT_EQ(len, receivedBytesLen);
    for(int i = 0; i < len; i++)
        EXPECT_EQ(std::to_integer<int>(msg[i]), std::to_integer<int>(bytes[i]));
}

/**
 * Host should be able to receive messages from all clients that are connected
 * simultaneously
 */
TEST_F(NetworkFixture, HostCanReceiveFromTwoClients)
{
    const size_t len = 3;
    l_host.startListening();
    l_client.connect();
    l_client2.connect();
    unsigned int id = l_host.acceptConnections().value_or(100u);
    unsigned int id2 = l_host.acceptConnections().value_or(101u);
    const std::array<std::byte, len> bytes = {std::byte{0x60}, std::byte{0x61}, std::byte{0x62}};
    l_client.sendBytes<len>(bytes);
    l_client2.sendBytes<len>(bytes);
    std::array<std::byte, len> msg;
    std::array<std::byte, len> msg2;
    size_t receivedBytesLen = 0;
    size_t receivedBytesLen2 = 0;
    l_host.receiveBytes<len>(id, msg, receivedBytesLen);
    l_host.receiveBytes<len>(id2, msg2, receivedBytesLen2);

    EXPECT_EQ(len, receivedBytesLen);
    EXPECT_EQ(len, receivedBytesLen2);

    for(int i = 0; i < len; i++)
    {
        EXPECT_EQ(std::to_integer<int>(msg[i]), std::to_integer<int>(bytes[i]));
        EXPECT_EQ(std::to_integer<int>(msg2[i]), std::to_integer<int>(bytes[i]));
    }
}

/**
 * Host should be able to send messages to all clients that are connected
 * simultaneously
 */
 TEST_F(NetworkFixture, HostCanSendToAllClients)
 {
    const size_t len = 3;
    l_host.startListening();
    l_client.connect();
    l_client2.connect();
    unsigned int id = l_host.acceptConnections().value_or(100u);
    unsigned int id2 = l_host.acceptConnections().value_or(101u);
    const std::array<std::byte, len> bytes = {std::byte{0x60}, std::byte{0x61}, std::byte{0x62}};
    l_host.broadcastBytes(bytes);
    std::array<std::byte, len> msg;
    std::array<std::byte, len> msg2;
    size_t receivedBytesLen = 0;
    size_t receivedBytesLen2 = 0;
    l_client.receiveBytes<len>(msg, receivedBytesLen);
    l_client2.receiveBytes<len>(msg2, receivedBytesLen2);

    EXPECT_EQ(len, receivedBytesLen);
    EXPECT_EQ(len, receivedBytesLen2);

    for(int i = 0; i < len; i++)
    {
        EXPECT_EQ(std::to_integer<int>(msg[i]), std::to_integer<int>(bytes[i]));
        EXPECT_EQ(std::to_integer<int>(msg2[i]), std::to_integer<int>(bytes[i]));
    } 
 }