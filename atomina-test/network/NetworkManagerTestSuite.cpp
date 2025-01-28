#include "NetworkManagerTestSuite.hpp"
#include "NetworkSystem.hpp"
#include "NetworkAttribute.hpp"

using namespace std::string_literals;

/**
 * Network manager should connect and receive message
 */
TEST_F(NetworkManagerFixture, NetworkManagerConnectionCanReceive)
{
    this->ctx.addSystemType<NetworkSystem>(0u);
    auto sys = this->ctx.getSystem<NetworkSystem>(0u);
    this->ctx.netManager.addMessageListener(ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::PORT_RESPONSE), sys);
    this->ctx.registerAttributeType<NetworkAttribute>(0u);
    auto objId = this->ctx.createObject();
    this->ctx.addAttribute(objId, 0u);
    const unsigned short port = 8899;
    const ATMA::URL address{"127.0.0.1"};
    auto listener = ATMA::SocketListener::makeSocketListener(port);
    this->ctx.netManager.startConnection(address, port);
    auto host = listener->acceptConnection();
    std::vector<unsigned char> sendingMessage = ATMA::NetworkSerde::serialize(ATMA::NetworkMessage{
        ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::PORT_RESPONSE),
        ATMA::Props{
            {{"port",
              std::pair<unsigned char, std::any>{ATMA::NetworkMessageValueType(ATMA::NetworkMessageValueEnum::INT), 4}}}

        }
    });
    std::span<unsigned char> send_buffer{sendingMessage};
    host->sendBytes(send_buffer, sendingMessage.size());
    auto respAttr = this->ctx.getAttribute<NetworkAttribute>(objId, 0u);
    this->ctx.netManager.stopConnection();
    ATMA::StopWatch stopwatch{};
    stopwatch.start();
    while(stopwatch.getElapsedDuration() < 10000000L
          && !respAttr->m_resps[ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::PORT_RESPONSE)].contains("port"))
    {
    }
    EXPECT_EQ(
        respAttr->m_resps[ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::PORT_RESPONSE)].getAs<int>("port"), 4
    );
}

/**
 * Network manager should receive multiple distinct messages
 */
TEST_F(NetworkManagerFixture, NetworkManagerConnectionCanReceiveMutliple)
{
    this->ctx.addSystemType<NetworkSystem>(0u);
    auto sys = this->ctx.getSystem<NetworkSystem>(0u);
    this->ctx.netManager.addMessageListener(ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::PORT_RESPONSE), sys);
    this->ctx.netManager.addMessageListener(ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::PORT_JOIN), sys);
    this->ctx.registerAttributeType<NetworkAttribute>(0u);
    auto objId = this->ctx.createObject();
    this->ctx.addAttribute(objId, 0u);
    const unsigned short port = 8899;
    const ATMA::URL address{"127.0.0.1"};
    auto listener = ATMA::SocketListener::makeSocketListener(port);
    this->ctx.netManager.startConnection(address, port);
    auto host = listener->acceptConnection();
    std::vector<unsigned char> sendingMessage = ATMA::NetworkSerde::serialize(ATMA::NetworkMessage{
        ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::PORT_RESPONSE),
        ATMA::Props{
            {{"port",
              std::pair<unsigned char, std::any>{ATMA::NetworkMessageValueType(ATMA::NetworkMessageValueEnum::INT), 4}}}

        }
    });
    std::span<unsigned char> send_buffer{sendingMessage};
    host->sendBytes(send_buffer, sendingMessage.size());
    sendingMessage = ATMA::NetworkSerde::serialize(ATMA::NetworkMessage{
        ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::PORT_JOIN),
        ATMA::Props{
            {{"port",
              std::pair<unsigned char, std::any>{ATMA::NetworkMessageValueType(ATMA::NetworkMessageValueEnum::INT), 5}}}

        }
    });
    std::span<unsigned char> send_buffer2{sendingMessage};
    host->sendBytes(send_buffer2, sendingMessage.size());
    auto respAttr = this->ctx.getAttribute<NetworkAttribute>(objId, 0u);
    ATMA::StopWatch stopwatch{};
    stopwatch.start();
    while(stopwatch.getElapsedDuration() < 10000000L
          && !respAttr->m_resps[ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::PORT_RESPONSE)].contains("port")
          && !respAttr->m_resps[ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::PORT_JOIN)].contains("port"))
    {
    }
    this->ctx.netManager.stopConnection();
    EXPECT_EQ(
        respAttr->m_resps[ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::PORT_RESPONSE)].getAs<int>("port"), 4
    );
    EXPECT_EQ(respAttr->m_resps[ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::PORT_JOIN)].getAs<int>("port"), 5);
}

/**
 * Network manager should buffer overflow messages
 */
TEST_F(NetworkManagerFixture, NetworkManagerCanHandleBufferOverflow)
{
    this->ctx.addSystemType<NetworkSystem>(0u);
    auto sys = this->ctx.getSystem<NetworkSystem>(0u);
    this->ctx.netManager.addMessageListener(ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::PORT_RESPONSE), sys);
    this->ctx.registerAttributeType<NetworkAttribute>(0u);
    auto objId = this->ctx.createObject();
    this->ctx.addAttribute(objId, 0u);
    const unsigned short port = 8899;
    const ATMA::URL address{"127.0.0.1"};
    auto listener = ATMA::SocketListener::makeSocketListener(port);
    this->ctx.netManager.startConnection(address, port);
    auto host = listener->acceptConnection();
    std::vector<unsigned char> sendingMessage = ATMA::NetworkSerde::serialize(ATMA::NetworkMessage{
        ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::PORT_RESPONSE),
        ATMA::Props{
            {{"port",
              std::pair<unsigned char, std::any>{ATMA::NetworkMessageValueType(ATMA::NetworkMessageValueEnum::INT), 4}}}

        }
    });
    unsigned short messageSize = ATMA::NETWORKMESSAGEBUFFERSIZE;
    for(int i = 0; i < sizeof(messageSize); i++)
    {
        short shift = i * sizeof(unsigned char) * 8;
        sendingMessage[i] = (messageSize >> shift) & 0xFF;
    }
    std::span<unsigned char> send_buffer{sendingMessage};
    host->sendBytes(send_buffer, sendingMessage.size());
    auto respAttr = this->ctx.getAttribute<NetworkAttribute>(objId, 0u);
    ATMA::StopWatch stopwatch{};
    stopwatch.start();
    while(stopwatch.getElapsedDuration() < 10000000L
          && !respAttr->m_resps[ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::PORT_RESPONSE)].contains("port"))
    {
    }
    EXPECT_EQ(
        respAttr->m_resps[ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::PORT_RESPONSE)].getAs<int>("port"), 4
    );
    EXPECT_EQ(respAttr->m_resps[ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::PORT_RESPONSE)].size(), 1);
}

/**
 * Network manager should handle large message with buffer overflow
 */
TEST_F(NetworkManagerFixture, NetworkManagerCanHandleBufferOverflowLargerThanBuffer)
{
    this->ctx.addSystemType<NetworkSystem>(0u);
    auto sys = this->ctx.getSystem<NetworkSystem>(0u);
    this->ctx.netManager.addMessageListener(ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::PORT_RESPONSE), sys);
    this->ctx.registerAttributeType<NetworkAttribute>(0u);
    auto objId = this->ctx.createObject();
    this->ctx.addAttribute(objId, 0u);
    const unsigned short port = 8899;
    const ATMA::URL address{"127.0.0.1"};
    auto listener = ATMA::SocketListener::makeSocketListener(port);
    this->ctx.netManager.startConnection(address, port);
    auto host = listener->acceptConnection();
    std::vector<unsigned char> sendingMessage = ATMA::NetworkSerde::serialize(ATMA::NetworkMessage{
        ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::PORT_RESPONSE),
        ATMA::Props{
            {{"port",
              std::pair<unsigned char, std::any>{ATMA::NetworkMessageValueType(ATMA::NetworkMessageValueEnum::INT), 4}}}

        }
    });
    unsigned short messageSize = ATMA::NETWORKMESSAGEBUFFERSIZE * 2;
    for(int i = 0; i < sizeof(messageSize); i++)
    {
        short shift = i * sizeof(unsigned char) * 8;
        sendingMessage[i] = (messageSize >> shift) & 0xFF;
    }
    std::span<unsigned char> send_buffer{sendingMessage};
    host->sendBytes(send_buffer, sendingMessage.size());
    auto respAttr = this->ctx.getAttribute<NetworkAttribute>(objId, 0u);
    ATMA::StopWatch stopwatch{};
    stopwatch.start();
    while(stopwatch.getElapsedDuration() < 10000000L
          && !respAttr->m_resps[ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::PORT_RESPONSE)].contains("port"))
    {
    }
    EXPECT_EQ(
        respAttr->m_resps[ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::PORT_RESPONSE)].getAs<int>("port"), 4
    );
    EXPECT_EQ(respAttr->m_resps[ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::PORT_RESPONSE)].size(), 1);
}

/**
 * Network manager can handle message with size smaller than message
 */
TEST_F(NetworkManagerFixture, NetworkManagerCanHandleBufferUnderflow)
{
    this->ctx.addSystemType<NetworkSystem>(0u);
    auto sys = this->ctx.getSystem<NetworkSystem>(0u);
    this->ctx.netManager.addMessageListener(ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::PORT_RESPONSE), sys);
    this->ctx.registerAttributeType<NetworkAttribute>(0u);
    auto objId = this->ctx.createObject();
    this->ctx.addAttribute(objId, 0u);
    const unsigned short port = 8899;
    const ATMA::URL address{"127.0.0.1"};
    auto listener = ATMA::SocketListener::makeSocketListener(port);
    this->ctx.netManager.startConnection(address, port);
    auto host = listener->acceptConnection();
    std::vector<unsigned char> sendingMessage = ATMA::NetworkSerde::serialize(ATMA::NetworkMessage{
        ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::PORT_RESPONSE),
        ATMA::Props{
            {{"port",
              std::pair<unsigned char, std::any>{ATMA::NetworkMessageValueType(ATMA::NetworkMessageValueEnum::INT), 4}}}

        }
    });
    unsigned short messageSize = 4;
    for(int i = 0; i < sizeof(messageSize); i++)
    {
        short shift = i * sizeof(unsigned char) * 8;
        sendingMessage[i] = (messageSize >> shift) & 0xFF;
    }
    std::span<unsigned char> send_buffer{sendingMessage};
    host->sendBytes(send_buffer, sendingMessage.size());
    auto respAttr = this->ctx.getAttribute<NetworkAttribute>(objId, 0u);
    ATMA::StopWatch stopwatch{};
    stopwatch.start();
    while(stopwatch.getElapsedDuration() < 10000000L
          && !respAttr->m_resps[ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::PORT_RESPONSE)].contains("port"))
    {
    }
    EXPECT_EQ(
        respAttr->m_resps[ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::PORT_RESPONSE)].getAs<int>("port"), 4
    );
}

/**
 * Network manager can handle message with size smaller than message with message larger than buffer
 */
TEST_F(NetworkManagerFixture, NetworkManagerCanHandleBufferUnderflowWithLargeMessage)
{
    this->ctx.addSystemType<NetworkSystem>(0u);
    auto sys = this->ctx.getSystem<NetworkSystem>(0u);
    this->ctx.netManager.addMessageListener(ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::INVALID), sys);
    this->ctx.registerAttributeType<NetworkAttribute>(0u);
    auto objId = this->ctx.createObject();
    this->ctx.addAttribute(objId, 0u);
    const unsigned short port = 8899;
    const ATMA::URL address{"127.0.0.1"};
    auto listener = ATMA::SocketListener::makeSocketListener(port);
    this->ctx.netManager.startConnection(address, port);
    auto host = listener->acceptConnection();
    std::vector<unsigned char> sendingMessage = ATMA::NetworkSerde::serialize(ATMA::NetworkMessage{
        ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::PORT_RESPONSE),
        ATMA::Props{
            {{"port",
              std::pair<unsigned char, std::any>{ATMA::NetworkMessageValueType(ATMA::NetworkMessageValueEnum::INT), 4}},
             {"time",
              std::pair<unsigned char, std::any>{
                  ATMA::NetworkMessageValueType(ATMA::NetworkMessageValueEnum::LONGLONG), 1234LL
              }},
             {"name",
              std::pair<unsigned char, std::any>{
                  ATMA::NetworkMessageValueType(ATMA::NetworkMessageValueEnum::STRING), "player"s
              }},
             {"roomName",
              std::pair<unsigned char, std::any>{
                  ATMA::NetworkMessageValueType(ATMA::NetworkMessageValueEnum::STRING), "This is a server room"s
              }}}

        }
    });
    unsigned short messageSize = 4;
    for(int i = 0; i < sizeof(messageSize); i++)
    {
        short shift = i * sizeof(unsigned char) * 8;
        sendingMessage[i] = (messageSize >> shift) & 0xFF;
    }
    std::span<unsigned char> send_buffer{sendingMessage};
    host->sendBytes(send_buffer, sendingMessage.size());
    auto respAttr = this->ctx.getAttribute<NetworkAttribute>(objId, 0u);
    ATMA::StopWatch stopwatch{};
    stopwatch.start();
    while(stopwatch.getElapsedDuration() < 10000000L
          && !respAttr->m_resps.contains(ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::INVALID)))
    {
    }
    EXPECT_TRUE(respAttr->m_resps.contains(ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::INVALID)));
}

/**
 * Network manager can send message to socket
 */
TEST_F(NetworkManagerFixture, NetworkManagerConnectionCanSend)
{
    const unsigned short port = 8899;
    const ATMA::URL address{"127.0.0.1"};
    auto listener = ATMA::SocketListener::makeSocketListener(port);
    this->ctx.netManager.startConnection(address, port);
    auto host = listener->acceptConnection();
    unsigned char recv_msg[ATMA::NETWORKMESSAGEBUFFERSIZE];
    std::span<unsigned char> recv_buffer{recv_msg};
    std::vector<unsigned char> wholeMessage{};
    size_t recv_bytes;
    size_t total_bytes;
    this->ctx.netManager.sendMessage(ATMA::NetworkMessage{
        ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::PORT_RESPONSE),
        ATMA::Props{
            {{"port",
              std::pair<unsigned char, std::any>{ATMA::NetworkMessageValueType(ATMA::NetworkMessageValueEnum::INT), 4}}}

        }
    });
    unsigned short messageSize;
    host->receiveBytes(recv_buffer, ATMA::NETWORKMESSAGEBUFFERSIZE, recv_bytes);
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
    while(total_bytes < messageSize)
    {
        host->receiveBytes(recv_buffer, ATMA::NETWORKMESSAGEBUFFERSIZE, recv_bytes);
        total_bytes += recv_bytes;
        for(int i = 0; i < recv_bytes; i++)
        {
            wholeMessage.emplace_back(recv_buffer[i]);
        }
    }
    size_t empty;
    ATMA::NetworkMessage nm = ATMA::NetworkSerde::deserialize(wholeMessage, empty);
    this->ctx.netManager.stopConnection();
    EXPECT_EQ(nm.values().getAs<int>("port"), 4);
}

/**
 * Network manager host can send to client socket
 */
TEST_F(NetworkManagerFixture, NetworkManagerHostCanSend)
{
    this->ctx.addSystemType<NetworkSystem>(0u);
    auto sys = this->ctx.getSystem<NetworkSystem>(0u);
    this->ctx.netManager.addMessageListener(
        ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::CONNECTION_STARTED), sys
    );
    this->ctx.registerAttributeType<NetworkAttribute>(0u);
    auto objId = this->ctx.createObject();
    this->ctx.addAttribute(objId, 0u);
    const unsigned short port = 8899;
    const ATMA::URL address{"127.0.0.1"};
    this->ctx.netManager.startHosting(port);
    auto sock = ATMA::Socket::makeSocket(address, port);
    auto respAttr = this->ctx.getAttribute<NetworkAttribute>(objId, 0u);
    ATMA::StopWatch stopwatch{};
    stopwatch.start();
    while(stopwatch.getElapsedDuration() < 10000000L && respAttr->m_connId == std::nullopt)
    {
    }
    this->ctx.netManager.stopHosting();
    if(respAttr->m_connId == std::nullopt)
    {
        ATMA_ENGINE_ERROR("could not fetch connection in time");
        ADD_FAILURE();
    }
    else
    {
        unsigned char recv_msg[ATMA::NETWORKMESSAGEBUFFERSIZE];
        std::span<unsigned char> recv_buffer{recv_msg};
        std::vector<unsigned char> wholeMessage{};
        size_t recv_bytes;
        size_t total_bytes;
        this->ctx.netManager.sendMessage(
            ATMA::NetworkMessage{
                ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::PORT_RESPONSE),
                ATMA::Props{
                    {{"port",
                      std::pair<unsigned char, std::any>{
                          ATMA::NetworkMessageValueType(ATMA::NetworkMessageValueEnum::INT), 4
                      }}}

                },

            },
            respAttr->m_connId
        );
        unsigned short messageSize;
        sock->receiveBytes(recv_buffer, ATMA::NETWORKMESSAGEBUFFERSIZE, recv_bytes);
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
        while(total_bytes < messageSize)
        {
            sock->receiveBytes(recv_buffer, ATMA::NETWORKMESSAGEBUFFERSIZE, recv_bytes);
            total_bytes += recv_bytes;
            for(int i = 0; i < recv_bytes; i++)
            {
                wholeMessage.emplace_back(recv_buffer[i]);
            }
        }
        size_t cursor;
        ATMA::NetworkMessage nm = ATMA::NetworkSerde::deserialize(wholeMessage, cursor);
        EXPECT_EQ(nm.values().getAs<int>("port"), 4);
    }
    ATMA_ENGINE_TRACE("end of unit test");
    this->ctx.netManager.stopConnection(respAttr->m_connId);
}

/**
 * Network manager host can receive message
 */
TEST_F(NetworkManagerFixture, NetworkManagerHostReceive)
{
    this->ctx.addSystemType<NetworkSystem>(0u);
    auto sys = this->ctx.getSystem<NetworkSystem>(0u);
    this->ctx.netManager.addMessageListener(
        ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::CONNECTION_STARTED), sys
    );
    this->ctx.netManager.addMessageListener(ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::PORT_RESPONSE), sys);
    this->ctx.registerAttributeType<NetworkAttribute>(0u);
    auto objId = this->ctx.createObject();
    this->ctx.addAttribute(objId, 0u);
    const unsigned short port = 8899;
    const ATMA::URL address{"127.0.0.1"};
    this->ctx.netManager.startHosting(port);
    auto sock = ATMA::Socket::makeSocket(address, port);
    auto respAttr = this->ctx.getAttribute<NetworkAttribute>(objId, 0u);
    ATMA::StopWatch stopwatch{};
    stopwatch.start();
    while(stopwatch.getElapsedDuration() < 10000000L && respAttr->m_connId == std::nullopt)
    {
    }
    this->ctx.netManager.stopHosting();
    if(respAttr->m_connId == std::nullopt)
    {
        ADD_FAILURE();
    }
    else
    {
        unsigned char recv_msg[ATMA::NETWORKMESSAGEBUFFERSIZE];
        std::span<unsigned char> recv_buffer{recv_msg};
        std::vector<unsigned char> wholeMessage{};
        size_t recv_bytes;
        size_t total_bytes;
        this->ctx.netManager.sendMessage(
            ATMA::NetworkMessage{
                ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::PORT_RESPONSE),
                ATMA::Props{
                    {{"port",
                      std::pair<unsigned char, std::any>{
                          ATMA::NetworkMessageValueType(ATMA::NetworkMessageValueEnum::INT), 4
                      }}}

                },

            },
            respAttr->m_connId
        );
        unsigned short messageSize;
        sock->receiveBytes(recv_buffer, ATMA::NETWORKMESSAGEBUFFERSIZE, recv_bytes);
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
        while(total_bytes < messageSize)
        {
            sock->receiveBytes(recv_buffer, ATMA::NETWORKMESSAGEBUFFERSIZE, recv_bytes);
            total_bytes += recv_bytes;
            for(int i = 0; i < recv_bytes; i++)
            {
                wholeMessage.emplace_back(recv_buffer[i]);
            }
        }
        size_t cursor;
        ATMA::NetworkMessage nm = ATMA::NetworkSerde::deserialize(wholeMessage,cursor);
        EXPECT_EQ(nm.values().getAs<int>("port"), 4);
    }
    this->ctx.netManager.stopConnection(respAttr->m_connId);
}