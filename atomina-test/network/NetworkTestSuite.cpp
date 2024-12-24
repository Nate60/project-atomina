#include "NetworkTestSuite.hpp"

using namespace std::string_literals;

/**
 * Sockets should be able to connect to an actively
 * listening socket listener
 */
TEST_F(NetworkFixture, SocketCanConnect)
{

    this->socket = ATMA::Socket::makeSocket(m_address, m_port);
    this->socket->setBlocking(false);
    EXPECT_NE(this->socket, nullptr);

}

/**
 * Socket Listener should return a pointer to a new socket
 * when accepting a connection
 */
TEST_F(NetworkFixture, ListenerCanAcceptConnection)
{
    this->socket = ATMA::Socket::makeSocket(m_address, m_port);
    this->socket->setBlocking(false);
    std::shared_ptr<ATMA::Socket> client = nullptr;
    while(client == nullptr)
    {
        client = this->listener->acceptConnection();
    }
    EXPECT_NE(client, nullptr);
    client = nullptr;
}

/**
 * Sockets should be able to send bytes across their
 * active connection
 */
TEST_F(NetworkFixture, SocketCanSend)
{
    this->socket = ATMA::Socket::makeSocket(m_address, m_port);
    this->socket->setBlocking(false);
    std::shared_ptr<ATMA::Socket> client = nullptr;
    while(client == nullptr)
    {
        client = this->listener->acceptConnection();
    }

    unsigned char msg[] = {'1', '2', '3', '\0'};

    std::span<unsigned char,4> buffer{msg};
    EXPECT_TRUE(this->socket->sendBytes(buffer, buffer.size()));
    client = nullptr;

}

/**
 * Sockets should be able to receive bytes that were sent across their
 * active connection
 */
TEST_F(NetworkFixture, SocketCanReceive)
{
    this->socket = ATMA::Socket::makeSocket(m_address, m_port);
    this->socket->setBlocking(false);
    std::shared_ptr<ATMA::Socket> client = nullptr;
    while(client == nullptr)
    {
        client = this->listener->acceptConnection();
    }

    unsigned char msg[] = {'1', '2', '3', '\0'};

    std::span<unsigned char, 4> buffer{msg};
    unsigned char recv_msg[4];
    std::span<unsigned char> bufferRecv{recv_msg};
    size_t recv_bytes;

    this->socket->sendBytes(buffer, buffer.size());
    client->receiveBytes(bufferRecv, 4, recv_bytes);
    for(int i = 0; i < 4; i++)
    {
        EXPECT_EQ(buffer[i], bufferRecv[i]);
    }
    EXPECT_TRUE(recv_bytes == 4);
    client = nullptr;

}

/**
 * Sockets should be able to send bytes across their
 * active connection
 */
TEST_F(NetworkFixture, SocketCantOverflow)
{
    this->socket = ATMA::Socket::makeSocket(m_address, m_port);
    this->socket->setBlocking(false);
    std::shared_ptr<ATMA::Socket> client = nullptr;
    while(client == nullptr)
    {
        client = this->listener->acceptConnection();
    }

    unsigned char msg[] = {'1', '2', '3', '\0'};

    std::span<unsigned char,4> buffer{msg};
    EXPECT_FALSE(this->socket->sendBytes(buffer, buffer.size() + 1));
    client = nullptr;

}

/**
 * Sockets should be able to receive bytes that were sent across their
 * active connection
 */
TEST_F(NetworkFixture, SocketCantUnderflow)
{
    this->socket = ATMA::Socket::makeSocket(m_address, m_port);
    this->socket->setBlocking(false);
    std::shared_ptr<ATMA::Socket> client = nullptr;
    while(client == nullptr)
    {
        client = this->listener->acceptConnection();
    }

    unsigned char msg[] = {'1', '2', '3', '\0'};

    std::span<unsigned char, 4> buffer{msg};
    unsigned char recv_msg[4];
    std::span<unsigned char> bufferRecv{recv_msg};
    size_t recv_bytes;

    this->socket->sendBytes(buffer, buffer.size() - 1);
    client->receiveBytes(bufferRecv, 5, recv_bytes);
    for(int i = 0; i < recv_bytes; i++)
    {
        EXPECT_EQ(buffer[i], bufferRecv[i]);
    }
    EXPECT_TRUE(recv_bytes == 3);
    client = nullptr;

}


/**
 * Sockets should be able to receive bytes from a message that were sent across their
 * active connection 
 */
TEST_F(NetworkFixture, SocketCanReceiveNetworkMessage)
{

    this->socket = ATMA::Socket::makeSocket(m_address, m_port);
    this->socket->setBlocking(false);
    std::shared_ptr<ATMA::Socket> client = nullptr;
    while(client == nullptr)
    {
        client = this->listener->acceptConnection();
    }
    std::vector<unsigned char> sendingMessage =
        ATMA::NetworkSerde::serialize(ATMA::NetworkMessage {
            ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::PORT_RESPONSE),
                ATMA::Props{
                    {
                        {
                            "port", 
                            std::pair<unsigned char,std::any>{ATMA::NetworkMessageValueType(ATMA::NetworkMessageValueEnum::INT), 4}
                        }
                    }
       
                }
        });
    std::span<unsigned char> send_buffer{sendingMessage};
    unsigned char recv_msg[ATMA::NETWORKMESSAGEBUFFERSIZE];
    std::span<unsigned char> recv_buffer{recv_msg};
    size_t recv_bytes;
    this->socket->sendBytes(send_buffer, sendingMessage.size());
    client->receiveBytes(recv_buffer, ATMA::NETWORKMESSAGEBUFFERSIZE, recv_bytes);
    std::vector<unsigned char> v{recv_msg,recv_msg + recv_bytes};
    size_t cursor;
    ATMA::NetworkMessage nm = ATMA::NetworkSerde::deserialize(v,cursor);
    client = nullptr;
    EXPECT_EQ(nm.values().getAs<int>("port"), 4);

}

/**
 * Sockets should be able to receive bytes from a message that were sent across their
 * active connection 
 */
TEST_F(NetworkFixture, SocketCanReceiveNetworkMessageLargerThanBuffer)
{

    this->socket = ATMA::Socket::makeSocket(m_address, m_port);
    this->socket->setBlocking(false);
    std::shared_ptr<ATMA::Socket> client = nullptr;
    while(client == nullptr)
    {
        client = this->listener->acceptConnection();
    }
    std::vector<unsigned char> sendingMessage =
        ATMA::NetworkSerde::serialize(ATMA::NetworkMessage {
            ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::PORT_RESPONSE),
                ATMA::Props{
                    {
                        {
                            "port", 
                            std::pair<unsigned char,std::any>{ATMA::NetworkMessageValueType(ATMA::NetworkMessageValueEnum::INT), 4}
                        },
                        {
                            "ServerName",
                            std::pair<unsigned char, std::any>{ATMA::NetworkMessageValueType(ATMA::NetworkMessageValueEnum::STRING), "MyServer"s}
                        },
                        {
                            "PlayerName",
                            std::pair<unsigned char, std::any>{ATMA::NetworkMessageValueType(ATMA::NetworkMessageValueEnum::STRING), "Player 1"s}
                        },
                        {
                            "TimeStamp",
                            std::pair<unsigned char,std::any>{ATMA::NetworkMessageValueType(ATMA::NetworkMessageValueEnum::LONGLONG), 123456789LL}
                        }
                    }
       
                }
        });
    std::span<unsigned char> send_buffer{sendingMessage};
    unsigned char recv_msg[ATMA::NETWORKMESSAGEBUFFERSIZE];
    std::span<unsigned char> recv_buffer{recv_msg};
    std::vector<unsigned char> wholeMessage{};
    size_t recv_bytes;
    size_t total_bytes;
    this->socket->sendBytes(send_buffer, sendingMessage.size());
    unsigned short messageSize;
    client->receiveBytes(recv_buffer, ATMA::NETWORKMESSAGEBUFFERSIZE, recv_bytes);
    total_bytes = recv_bytes;
    for(int i = 0; i < recv_bytes; i++)
    {
        wholeMessage.emplace_back(recv_buffer[i]);
    }
    std::copy(
            recv_buffer.begin(),
            recv_buffer.begin() + sizeof(unsigned short),
            reinterpret_cast<unsigned char *>(&messageSize)
    );
    while(total_bytes < messageSize){
        client->receiveBytes(recv_buffer, ATMA::NETWORKMESSAGEBUFFERSIZE, recv_bytes);
        total_bytes += recv_bytes;
        for(int i = 0; i < recv_bytes; i++)
        {
            wholeMessage.emplace_back(recv_buffer[i]);
        }
    }
    size_t cursor;
    ATMA::NetworkMessage nm = ATMA::NetworkSerde::deserialize(wholeMessage,cursor);
    client = nullptr;
    EXPECT_EQ(nm.values().getAs<int>("port"), 4);
    EXPECT_EQ(nm.values().getAs<std::string>("PlayerName"), "Player 1"s);

}