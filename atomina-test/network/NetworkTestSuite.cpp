#include "NetworkTestSuite.hpp"

using namespace std::string_literals;

/**
 * Sockets should be able to connect to an actively
 * listening socket listener
 */
TEST_F(NetworkFixture, SocketCanConnect)
{
    this->listener->startListening();
    EXPECT_TRUE(this->socket->connectSocket(m_address, m_port));
}

/**
 * Socket Listener should return a pointer to a new socket
 * when accepting a connection
 */
TEST_F(NetworkFixture, ListenerCanAcceptConnection)
{
    this->listener->startListening();
    this->socket->connectSocket(m_address, m_port);
    auto client = this->listener->acceptConnection();
    EXPECT_NE(client, nullptr);
    client->closeSocket();
}

/**
 * Sockets should be able to send bytes across their
 * active connection
 */
TEST_F(NetworkFixture, SocketCanSend)
{
    this->listener->startListening();
    this->socket->connectSocket(m_address, m_port);
    auto client = this->listener->acceptConnection();

    char msg[] = {'1', '2', '3', '\0'};

    std::span<char> buffer{msg};
    EXPECT_TRUE(this->socket->sendBytes(buffer));
    client->closeSocket();
}

/**
 * Sockets should be able to receive bytes that were sent across their
 * active connection
 */
TEST_F(NetworkFixture, SocketCanReceive)
{
    this->listener->startListening();
    this->socket->connectSocket(m_address, m_port);
    auto client = this->listener->acceptConnection();

    char send_msg[] = {'1', '2', '3', '\0'};
    char recv_msg[] = {'0', '0', '0', '\0'};
    std::span<char> send_buffer{send_msg};
    std::span<char> recv_buffer{recv_msg};
    size_t recv_bytes;

    this->socket->sendBytes(send_buffer);
    client->receiveBytes(recv_buffer, recv_bytes);
    for(int i = 0; i < 4; i++)
    {
        EXPECT_TRUE(recv_buffer.data()[i] == send_buffer.data()[i]);
    }
    EXPECT_TRUE(recv_bytes == 4);
    client->closeSocket();
}

/**
 * Hosts should return an id when accepting an active connection
 * from a connecting client
 */
TEST_F(NetworkClientHostFixture, HostCanAcceptConnection)
{
    this->m_host.startListening();
    this->m_client.connect();
    EXPECT_TRUE(this->m_host.acceptConnections() != std::nullopt);
}

/**
 * Clients should be able to send data to their connected host
 * and the host should receive the same data
 */
TEST_F(NetworkClientHostFixture, ClientCanSend)
{
    this->m_host.startListening();
    this->m_client.connect();
    auto client = this->m_host.acceptConnections();
    this->m_host.setBlocking(client.value(), false);

    char send_msg[] = {'1', '2', '3', '\0'};
    char recv_msg[] = {'0', '0', '0', '\0'};
    std::span<char> send_buffer{send_msg};
    std::span<char> recv_buffer{recv_msg};
    size_t recv_bytes;

    this->m_client.sendBytes(send_buffer);
    this->m_host.receiveBytes(client.value(), recv_buffer, recv_bytes);
    ATMA_ENGINE_TRACE("Starting data check...");
    for(int i = 0; i < 4; i++)
    {
        EXPECT_TRUE(recv_buffer.data()[i] == send_buffer.data()[i]);
    }
    ATMA_ENGINE_TRACE("Ending data check...");
    EXPECT_TRUE(recv_bytes == 4);
    ATMA_ENGINE_TRACE("Test complete...");
}

/**
 * Hosts should be able to send to their connected clients
 * and the data the received should be the same
 */
TEST_F(NetworkClientHostFixture, HostCanSend)
{
    this->m_host.startListening();
    this->m_client.connect();
    auto client = this->m_host.acceptConnections();
    this->m_host.setBlocking(client.value(), false);

    char send_msg[] = {'1', '2', '3', '\0'};
    char recv_msg[] = {'0', '0', '0', '\0'};
    std::span<char> send_buffer{send_msg};
    std::span<char> recv_buffer{recv_msg};
    size_t recv_bytes;

    this->m_host.sendBytes(client.value(), send_buffer);
    this->m_client.receiveBytes(recv_buffer, recv_bytes);
    for(int i = 0; i < 4; i++)
    {
        EXPECT_TRUE(recv_buffer.data()[i] == send_buffer.data()[i]);
    }
    EXPECT_TRUE(recv_bytes == 4);
}

/**
 * Hosts should be able to have more than one active connection at
 * a time
 */
TEST_F(NetworkClientHostFixture, HostCanAcceptTwoConnections)
{
    ATMA::NetworkClient secondClient{this->m_address, this->m_port};
    secondClient.setBlocking(false);
    this->m_host.startListening();
    this->m_client.connect();
    auto firstConn = this->m_host.acceptConnections();
    secondClient.connect();
    auto secondConn = this->m_host.acceptConnections();
    EXPECT_TRUE(firstConn != std::nullopt);
    EXPECT_TRUE(secondConn != std::nullopt);
    EXPECT_TRUE(firstConn.value() != secondConn.value());
    secondClient.disconnect();
}

/**
 * Hosts should be able to receive messages from all active clients
 */
TEST_F(NetworkClientHostFixture, HostCanReceiveTwoMessages)
{
    ATMA::NetworkClient secondClient{this->m_address, this->m_port};
    secondClient.setBlocking(false);
    this->m_host.startListening();
    this->m_client.connect();
    auto firstConn = this->m_host.acceptConnections();
    this->m_host.setBlocking(firstConn.value(), false);
    secondClient.connect();
    auto secondConn = this->m_host.acceptConnections();
    m_host.setBlocking(secondConn.value(), false);

    char send_msg[] = {'1', '2', '3', '\0'};
    char recv_msg1[] = {'0', '0', '0', '\0'};
    char recv_msg2[] = {'0', '0', '0', '\0'};
    std::span<char> send_buffer{send_msg};
    std::span<char> recv_buffer1{recv_msg1};
    std::span<char> recv_buffer2{recv_msg2};
    size_t recv_bytes1;
    size_t recv_bytes2;

    this->m_client.sendBytes(send_buffer);
    this->m_host.receiveBytes(firstConn.value(), recv_buffer1, recv_bytes1);

    secondClient.sendBytes(send_buffer);
    this->m_host.receiveBytes(secondConn.value(), recv_buffer2, recv_bytes2);

    for(int i = 0; i < 4; i++)
    {
        EXPECT_TRUE(recv_buffer1.data()[i] == send_buffer.data()[i]);
        EXPECT_TRUE(recv_buffer2.data()[i] == send_buffer.data()[i]);
    }
    EXPECT_TRUE(recv_bytes1 == 4);
    EXPECT_TRUE(recv_bytes2 == 4);

    secondClient.disconnect();
}

/**
 * Hosts should be able to send messages to all active clients
 */
TEST_F(NetworkClientHostFixture, HostCanSendTwoMessages)
{
    ATMA::NetworkClient secondClient{this->m_address, this->m_port};
    secondClient.setBlocking(false);
    this->m_host.startListening();
    this->m_client.connect();
    auto firstConn = this->m_host.acceptConnections();
    this->m_host.setBlocking(firstConn.value(), false);
    secondClient.connect();
    auto secondConn = this->m_host.acceptConnections();
    m_host.setBlocking(secondConn.value(), false);

    char send_msg[] = {'1', '2', '3', '\0'};
    char recv_msg1[] = {'0', '0', '0', '\0'};
    char recv_msg2[] = {'0', '0', '0', '\0'};
    std::span<char> send_buffer{send_msg};
    std::span<char> recv_buffer1{recv_msg1};
    std::span<char> recv_buffer2{recv_msg2};
    size_t recv_bytes1;
    size_t recv_bytes2;

    this->m_host.sendBytes(firstConn.value(), send_buffer);
    this->m_client.receiveBytes(recv_buffer1, recv_bytes1);

    this->m_host.sendBytes(secondConn.value(), send_buffer);
    secondClient.receiveBytes(recv_buffer2, recv_bytes2);

    for(int i = 0; i < 4; i++)
    {
        EXPECT_TRUE(recv_buffer1.data()[i] == send_buffer.data()[i]);
        EXPECT_TRUE(recv_buffer2.data()[i] == send_buffer.data()[i]);
    }
    EXPECT_TRUE(recv_bytes1 == 4);
    EXPECT_TRUE(recv_bytes2 == 4);

    secondClient.disconnect();
}

/**
 * Broadcasting a message should send it to all active clients
 */
TEST_F(NetworkClientHostFixture, HostCanBroadcastMessages)
{
    ATMA::NetworkClient secondClient{this->m_address, this->m_port};
    secondClient.setBlocking(false);
    this->m_host.startListening();
    this->m_client.connect();
    auto firstConn = this->m_host.acceptConnections();
    this->m_host.setBlocking(firstConn.value(), false);
    secondClient.connect();
    auto secondConn = this->m_host.acceptConnections();
    m_host.setBlocking(secondConn.value(), false);

    char send_msg[] = {'1', '2', '3', '\0'};
    char recv_msg1[] = {'0', '0', '0', '\0'};
    char recv_msg2[] = {'0', '0', '0', '\0'};
    std::span<char> send_buffer{send_msg};
    std::span<char> recv_buffer1{recv_msg1};
    std::span<char> recv_buffer2{recv_msg2};
    size_t recv_bytes1;
    size_t recv_bytes2;

    this->m_host.broadcastBytes(send_buffer);
    this->m_client.receiveBytes(recv_buffer1, recv_bytes1);
    secondClient.receiveBytes(recv_buffer2, recv_bytes2);

    for(int i = 0; i < 4; i++)
    {
        EXPECT_TRUE(recv_buffer1.data()[i] == send_buffer.data()[i]);
        EXPECT_TRUE(recv_buffer2.data()[i] == send_buffer.data()[i]);
    }
    EXPECT_TRUE(recv_bytes1 == 4);
    EXPECT_TRUE(recv_bytes2 == 4);

    secondClient.disconnect();
}