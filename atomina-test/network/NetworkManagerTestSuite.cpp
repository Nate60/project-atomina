#include "NetworkManagerTestSuite.hpp"
#include "AtominaTest.hpp"
#include "NetworkSystem.hpp"
#include "NetworkAttribute.hpp"
#include <future>
#include <semaphore>

using namespace std::string_literals;
using namespace std::chrono_literals;

/**
 * Network manager should connect and receive message
 */
TEST_F(NetworkManagerFixture, NetworkManagerConnectionCanReceive)
{
    GTEST_SKIP();

    struct signals
    {
        const unsigned short port = 8899;
        std::binary_semaphore m_listenerUp{0}, m_recvConnStart{0}, m_sendMessage{0};
    };

    signals *sigs = new signals{};
    auto *ctx = makeContext();
    ctx->m_sysMan->addSystemType<NetworkSystem>(ctx, 0u);
    auto sys = ctx->m_sysMan->getSystem<NetworkSystem>(0u);
    ctx->m_attrMan->registerAttributeType<NetworkAttribute>(0u);
    auto objId = ctx->m_attrMan->createObject();
    ctx->m_attrMan->addAttribute(ctx, objId, 0u);
    ctx->m_netMan->addMessageListener(ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::PORT_RESPONSE), sys);
    auto connFuture = std::async(
        std::launch::async,
        [](ATMA::ATMAContext *ctx, signals *sigs)
        {
            const ATMA::URL address{"127.0.0.1"};
            sigs->m_listenerUp.acquire();
            ctx->m_netMan->startConnection(ctx, address, sigs->port);
            sigs->m_recvConnStart.release();
            sigs->m_sendMessage.acquire();
            ctx->m_netMan->stopConnection();
        },
        ctx,
        sigs
    );
    auto hostFuture = std::async(
        std::launch::async,
        [](signals *sigs)
        {
            auto listener = ATMA::SocketListener::makeSocketListener(sigs->port);
            sigs->m_listenerUp.release();
            sigs->m_recvConnStart.acquire();
            auto host = listener->acceptConnection();
            host->setBlocking(true);
            std::vector<unsigned char> sendingMessage = ATMA::NetworkSerde::serialize(
                ATMA::NetworkMessage{
                    ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::PORT_RESPONSE),
                    ATMA::Props{
                        {{"port",
                          std::pair<unsigned char, std::any>{
                              ATMA::NetworkMessageValueType(ATMA::NetworkMessageValueEnum::INT), 4
                          }}}

                    }
                }
            );
            std::span<unsigned char> send_buffer{sendingMessage};
            host->sendBytes(send_buffer, sendingMessage.size());
            sigs->m_sendMessage.release();
        },
        sigs
    );
    hostFuture.wait_for(3s);
    connFuture.wait_for(3s);
    auto respAttr = ctx->m_attrMan->getAttribute<NetworkAttribute>(objId, 0u);
    EXPECT_EQ(
        respAttr->m_resps[ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::PORT_RESPONSE)].getAs<int>("port"), 4
    );
    delete sigs;
    delete ctx;
}

/**
 * Network manager should receive multiple distinct messages
 */
TEST_F(NetworkManagerFixture, NetworkManagerConnectionCanReceiveMutliple)
{
    GTEST_SKIP();

    struct signals
    {
        const unsigned short port = 8899;
        std::binary_semaphore m_listenerUp{0}, m_recvConnStart{0}, m_sendMessage{0};
    };

    signals *sigs = new signals{};
    auto *ctx = makeContext();
    ctx->m_sysMan->addSystemType<NetworkSystem>(ctx, 0u);
    auto sys = ctx->m_sysMan->getSystem<NetworkSystem>(0u);
    ctx->m_netMan->addMessageListener(ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::PORT_RESPONSE), sys);
    ctx->m_netMan->addMessageListener(ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::PORT_JOIN), sys);
    ctx->m_attrMan->registerAttributeType<NetworkAttribute>(0u);
    auto objId = ctx->m_attrMan->createObject();
    ctx->m_attrMan->addAttribute(ctx, objId, 0u);
    auto respAttr = ctx->m_attrMan->getAttribute<NetworkAttribute>(objId, 0u);
    auto connFuture = std::async(
        std::launch::async,
        [](ATMA::ATMAContext *ctx, signals *sigs)
        {
            const ATMA::URL address{"127.0.0.1"};
            sigs->m_listenerUp.acquire();
            ctx->m_netMan->startConnection(ctx, address, sigs->port);
            sigs->m_recvConnStart.release();
            sigs->m_sendMessage.acquire();
            ctx->m_netMan->stopConnection();
        },
        ctx,
        sigs
    );
    auto hostFuture = std::async(
        std::launch::async,
        [](signals *sigs, std::shared_ptr<NetworkAttribute> attr)
        {
            auto listener = ATMA::SocketListener::makeSocketListener(sigs->port);
            sigs->m_listenerUp.release();
            sigs->m_recvConnStart.acquire();
            auto host = listener->acceptConnection();
            host->setBlocking(true);
            std::vector<unsigned char> sendingMessage = ATMA::NetworkSerde::serialize(
                ATMA::NetworkMessage{
                    ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::PORT_RESPONSE),
                    ATMA::Props{
                        {{"port",
                          std::pair<unsigned char, std::any>{
                              ATMA::NetworkMessageValueType(ATMA::NetworkMessageValueEnum::INT), 4
                          }}}

                    }
                }
            );
            std::span<unsigned char> send_buffer{sendingMessage};
            host->sendBytes(send_buffer, sendingMessage.size());
            // wait till first message is consumed
            while(attr->m_resps.find(ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::PORT_RESPONSE))
                  == attr->m_resps.end())
                ;
            sendingMessage = ATMA::NetworkSerde::serialize(
                ATMA::NetworkMessage{
                    ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::PORT_JOIN),
                    ATMA::Props{
                        {{"port",
                          std::pair<unsigned char, std::any>{
                              ATMA::NetworkMessageValueType(ATMA::NetworkMessageValueEnum::INT), 5
                          }}}

                    }
                }
            );
            std::span<unsigned char> send_buffer2{sendingMessage};
            host->sendBytes(send_buffer2, sendingMessage.size());
            sigs->m_sendMessage.release();
        },
        sigs,
        respAttr
    );
    hostFuture.wait_for(3s);
    connFuture.wait_for(3s);
    EXPECT_EQ(
        respAttr->m_resps[ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::PORT_RESPONSE)].getAs<int>("port"), 4
    );
    EXPECT_EQ(respAttr->m_resps[ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::PORT_JOIN)].getAs<int>("port"), 5);
    delete sigs;
    delete ctx;
}

/**
 * Network manager should buffer overflow messages
 */
TEST_F(NetworkManagerFixture, NetworkManagerCanHandleBufferOverflow)
{
    GTEST_SKIP();

    struct signals
    {
        const unsigned short port = 8899;
        std::binary_semaphore m_listenerUp{0}, m_recvConnStart{0}, m_sendMessage{0};
    };

    signals *sigs = new signals{};
    auto *ctx = makeContext();
    ctx->m_sysMan->addSystemType<NetworkSystem>(ctx, 0u);
    auto sys = ctx->m_sysMan->getSystem<NetworkSystem>(0u);
    ctx->m_attrMan->registerAttributeType<NetworkAttribute>(0u);
    auto objId = ctx->m_attrMan->createObject();
    ctx->m_attrMan->addAttribute(ctx, objId, 0u);
    ctx->m_netMan->addMessageListener(ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::PORT_RESPONSE), sys);
    auto connFuture = std::async(
        std::launch::async,
        [](ATMA::ATMAContext *ctx, signals *sigs)
        {
            const ATMA::URL address{"127.0.0.1"};
            sigs->m_listenerUp.acquire();
            ctx->m_netMan->startConnection(ctx, address, sigs->port);
            sigs->m_recvConnStart.release();
            sigs->m_sendMessage.acquire();
            ctx->m_netMan->stopConnection();
        },
        ctx,
        sigs
    );
    auto hostFuture = std::async(
        std::launch::async,
        [](signals *sigs)
        {
            auto listener = ATMA::SocketListener::makeSocketListener(sigs->port);
            sigs->m_listenerUp.release();
            sigs->m_recvConnStart.acquire();
            auto host = listener->acceptConnection();
            host->setBlocking(true);
            std::vector<unsigned char> sendingMessage = ATMA::NetworkSerde::serialize(
                ATMA::NetworkMessage{
                    ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::PORT_RESPONSE),
                    ATMA::Props{
                        {{"port",
                          std::pair<unsigned char, std::any>{
                              ATMA::NetworkMessageValueType(ATMA::NetworkMessageValueEnum::INT), 4
                          }}}

                    }
                }
            );
            unsigned short messageSize = ATMA::NETWORKMESSAGEBUFFERSIZE;
            for(size_t i = 0; i < sizeof(messageSize); i++)
            {
                short shift = i * sizeof(unsigned char) * 8;
                sendingMessage[i] = (messageSize >> shift) & 0xFF;
            }
            std::span<unsigned char> send_buffer{sendingMessage};
            host->sendBytes(send_buffer, sendingMessage.size());
            sigs->m_sendMessage.release();
        },
        sigs
    );
    hostFuture.wait_for(3s);
    connFuture.wait_for(3s);
    auto respAttr = ctx->m_attrMan->getAttribute<NetworkAttribute>(objId, 0u);
    EXPECT_EQ(
        respAttr->m_resps[ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::PORT_RESPONSE)].getAs<int>("port"), 4
    );
    EXPECT_EQ(respAttr->m_resps[ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::PORT_RESPONSE)].size(), 1);
    delete sigs;
    delete ctx;
}

/**
 * Network manager should handle large message with buffer overflow
 */
TEST_F(NetworkManagerFixture, NetworkManagerCanHandleBufferOverflowLargerThanBuffer)
{
    GTEST_SKIP();

    struct signals
    {
        const unsigned short port = 8899;
        std::binary_semaphore m_listenerUp{0}, m_recvConnStart{0}, m_sendMessage{0};
    };

    signals *sigs = new signals{};
    auto *ctx = makeContext();
    ctx->m_sysMan->addSystemType<NetworkSystem>(ctx, 0u);
    auto sys = ctx->m_sysMan->getSystem<NetworkSystem>(0u);
    ctx->m_attrMan->registerAttributeType<NetworkAttribute>(0u);
    auto objId = ctx->m_attrMan->createObject();
    ctx->m_attrMan->addAttribute(ctx, objId, 0u);
    ctx->m_netMan->addMessageListener(ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::PORT_RESPONSE), sys);
    auto connFuture = std::async(
        std::launch::async,
        [](ATMA::ATMAContext *ctx, signals *sigs)
        {
            const ATMA::URL address{"127.0.0.1"};
            sigs->m_listenerUp.acquire();
            ctx->m_netMan->startConnection(ctx, address, sigs->port);
            sigs->m_recvConnStart.release();
            sigs->m_sendMessage.acquire();
            ctx->m_netMan->stopConnection();
        },
        ctx,
        sigs
    );
    auto hostFuture = std::async(
        std::launch::async,
        [](signals *sigs)
        {
            auto listener = ATMA::SocketListener::makeSocketListener(sigs->port);
            sigs->m_listenerUp.release();
            sigs->m_recvConnStart.acquire();
            auto host = listener->acceptConnection();
            host->setBlocking(true);
            std::vector<unsigned char> sendingMessage = ATMA::NetworkSerde::serialize(
                ATMA::NetworkMessage{
                    ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::PORT_RESPONSE),
                    ATMA::Props{
                        {{"port",
                          std::pair<unsigned char, std::any>{
                              ATMA::NetworkMessageValueType(ATMA::NetworkMessageValueEnum::INT), 4
                          }}}

                    }
                }
            );
            unsigned short messageSize = ATMA::NETWORKMESSAGEBUFFERSIZE * 2;
            for(size_t i = 0; i < sizeof(messageSize); i++)
            {
                short shift = i * sizeof(unsigned char) * 8;
                sendingMessage[i] = (messageSize >> shift) & 0xFF;
            }
            std::span<unsigned char> send_buffer{sendingMessage};
            host->sendBytes(send_buffer, sendingMessage.size());
            sigs->m_sendMessage.release();
        },
        sigs
    );
    hostFuture.wait_for(3s);
    connFuture.wait_for(3s);
    auto respAttr = ctx->m_attrMan->getAttribute<NetworkAttribute>(objId, 0u);
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
    GTEST_SKIP();

    struct signals
    {
        const unsigned short port = 8899;
        std::binary_semaphore m_listenerUp{0}, m_recvConnStart{0}, m_sendMessage{0};
    };

    signals *sigs = new signals{};
    auto *ctx = makeContext();
    ctx->m_sysMan->addSystemType<NetworkSystem>(ctx, 0u);
    auto sys = ctx->m_sysMan->getSystem<NetworkSystem>(0u);
    ctx->m_attrMan->registerAttributeType<NetworkAttribute>(0u);
    auto objId = ctx->m_attrMan->createObject();
    ctx->m_attrMan->addAttribute(ctx, objId, 0u);
    ctx->m_netMan->addMessageListener(ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::PORT_RESPONSE), sys);
    auto connFuture = std::async(
        std::launch::async,
        [](ATMA::ATMAContext *ctx, signals *sigs)
        {
            const ATMA::URL address{"127.0.0.1"};
            sigs->m_listenerUp.acquire();
            ctx->m_netMan->startConnection(ctx, address, sigs->port);
            sigs->m_recvConnStart.release();
            sigs->m_sendMessage.acquire();
            ctx->m_netMan->stopConnection();
        },
        ctx,
        sigs
    );
    auto hostFuture = std::async(
        std::launch::async,
        [](signals *sigs)
        {
            auto listener = ATMA::SocketListener::makeSocketListener(sigs->port);
            sigs->m_listenerUp.release();
            sigs->m_recvConnStart.acquire();
            auto host = listener->acceptConnection();
            host->setBlocking(true);
            std::vector<unsigned char> sendingMessage = ATMA::NetworkSerde::serialize(
                ATMA::NetworkMessage{
                    ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::PORT_RESPONSE),
                    ATMA::Props{
                        {{"port",
                          std::pair<unsigned char, std::any>{
                              ATMA::NetworkMessageValueType(ATMA::NetworkMessageValueEnum::INT), 4
                          }}}

                    }
                }
            );
            unsigned short messageSize = 4;
            for(size_t i = 0; i < sizeof(messageSize); i++)
            {
                short shift = i * sizeof(unsigned char) * 8;
                sendingMessage[i] = (messageSize >> shift) & 0xFF;
            }
            std::span<unsigned char> send_buffer{sendingMessage};
            host->sendBytes(send_buffer, sendingMessage.size());
            sigs->m_sendMessage.release();
        },
        sigs
    );
    hostFuture.wait_for(3s);
    connFuture.wait_for(3s);
    auto respAttr = ctx->m_attrMan->getAttribute<NetworkAttribute>(objId, 0u);
    EXPECT_EQ(
        respAttr->m_resps[ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::PORT_RESPONSE)].getAs<int>("port"), 4
    );
}

/**
 * Network manager can send message to socket
 */
TEST_F(NetworkManagerFixture, NetworkManagerConnectionCanSend)
{
    GTEST_SKIP();

    struct signals
    {
        const unsigned short port = 8899;
        std::binary_semaphore m_listenerUp{0}, m_recvConnStart{0}, m_sendConnStart{0}, m_sendMessage{0},
            m_recvMessage{0};
    };

    std::vector<unsigned char> wholeMessage{};
    signals *sigs = new signals{};
    auto *ctx = makeContext();
    ctx->m_sysMan->addSystemType<NetworkSystem>(ctx, 0u);
    auto sys = ctx->m_sysMan->getSystem<NetworkSystem>(0u);
    ctx->m_attrMan->registerAttributeType<NetworkAttribute>(0u);
    auto objId = ctx->m_attrMan->createObject();
    ctx->m_attrMan->addAttribute(ctx, objId, 0u);
    ctx->m_netMan->addMessageListener(ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::PORT_RESPONSE), sys);
    auto connFuture = std::async(
        std::launch::async,
        [](ATMA::ATMAContext *ctx, signals *sigs)
        {
            const ATMA::URL address{"127.0.0.1"};
            sigs->m_listenerUp.acquire();
            ctx->m_netMan->startConnection(ctx, address, sigs->port);
            sigs->m_recvConnStart.release();
            sigs->m_sendConnStart.acquire();
            // send message
            ctx->m_netMan->sendMessage(
                ATMA::NetworkMessage{
                    ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::PORT_RESPONSE),
                    ATMA::Props{
                        {{"port",
                          std::pair<unsigned char, std::any>{
                              ATMA::NetworkMessageValueType(ATMA::NetworkMessageValueEnum::INT), 4
                          }}}

                    }
                }
            );
            sigs->m_sendMessage.release();
            sigs->m_recvMessage.acquire();
            ctx->m_netMan->stopConnection();
        },
        ctx,
        sigs
    );
    auto hostFuture = std::async(
        std::launch::async,
        [](signals *sigs, std::vector<unsigned char> *msg)
        {
            auto listener = ATMA::SocketListener::makeSocketListener(sigs->port);
            sigs->m_listenerUp.release();
            sigs->m_recvConnStart.acquire();
            auto host = listener->acceptConnection();
            host->setBlocking(true);
            sigs->m_sendConnStart.release();
            sigs->m_sendMessage.acquire();
            unsigned char recv_msg[ATMA::NETWORKMESSAGEBUFFERSIZE];
            std::span<unsigned char> recv_buffer{recv_msg};
            size_t recv_bytes;
            size_t total_bytes;
            unsigned short messageSize;
            host->receiveBytes(recv_buffer, ATMA::NETWORKMESSAGEBUFFERSIZE, recv_bytes);
            total_bytes = recv_bytes;
            for(size_t i = 0; i < recv_bytes; i++)
            {
                msg->emplace_back(recv_buffer[i]);
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
                for(size_t i = 0; i < recv_bytes; i++)
                {
                    msg->emplace_back(recv_buffer[i]);
                }
            }
            sigs->m_recvMessage.release();
        },
        sigs,
        &wholeMessage
    );
    hostFuture.wait_for(3s);
    connFuture.wait_for(3s);
    size_t empty;
    ATMA::NetworkMessage nm = ATMA::NetworkSerde::deserialize(wholeMessage, empty);
    EXPECT_EQ(nm.values().getAs<int>("port"), 4);
    delete sigs;
    delete ctx;
}

/**
 * Network manager host can send to client socket
 */
TEST_F(NetworkManagerFixture, NetworkManagerHostCanSend)
{
    GTEST_SKIP();

    struct signals
    {
        const ATMA::URL address{"127.0.0.1"};
        const unsigned short port = 8899;
        std::binary_semaphore m_listenerUp{0}, m_recvConnStart{0}, m_sendConnStart{0}, m_sendMessage{0},
            m_recvMessage{0};
    };

    std::vector<unsigned char> wholeMessage{};
    signals *sigs = new signals{};
    auto *ctx = makeContext();
    ctx->m_sysMan->addSystemType<NetworkSystem>(ctx, 0u);
    auto sys = ctx->m_sysMan->getSystem<NetworkSystem>(0u);
    ctx->m_attrMan->registerAttributeType<NetworkAttribute>(0u);
    auto objId = ctx->m_attrMan->createObject();
    ctx->m_attrMan->addAttribute(ctx, objId, 0u);
    ctx->m_netMan->addMessageListener(ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::CONNECTION_STARTED), sys);
    auto respAttr = ctx->m_attrMan->getAttribute<NetworkAttribute>(objId, 0u);
    auto sendFuture = std::async(
        std::launch::async,
        [](ATMA::ATMAContext *ctx, signals *sigs, std::shared_ptr<NetworkAttribute> attr)
        {
            ctx->m_netMan->startHosting(ctx, sigs->port);
            sigs->m_listenerUp.release();
            sigs->m_recvConnStart.acquire();
            // get conn id
            while(attr->m_connId == std::nullopt)
                ;
            ATMA_ENGINE_TRACE("connection established");
            // connection established
            ctx->m_netMan->stopHosting();
            ATMA_ENGINE_TRACE("sending message");
            ctx->m_netMan->sendMessage(
                ATMA::NetworkMessage{
                    ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::PORT_RESPONSE),
                    ATMA::Props{
                        {{"port",
                          std::pair<unsigned char, std::any>{
                              ATMA::NetworkMessageValueType(ATMA::NetworkMessageValueEnum::INT), 4
                          }}}

                    }
                },
                attr->m_connId
            );
            sigs->m_sendMessage.release();
            sigs->m_recvMessage.acquire();
            ctx->m_netMan->stopConnection(attr->m_connId);
        },
        ctx,
        sigs,
        respAttr
    );
    auto recvFuture = std::async(
        std::launch::async,
        [](signals *sigs, std::vector<unsigned char> *msg)
        {
            sigs->m_listenerUp.acquire();
            auto sock = ATMA::Socket::makeSocket(sigs->address, sigs->port);
            sock->setBlocking(true);
            sigs->m_recvConnStart.release();
            sigs->m_sendMessage.acquire();
            unsigned short messageSize;
            unsigned char recv_msg[ATMA::NETWORKMESSAGEBUFFERSIZE];
            std::span<unsigned char> recv_buffer{recv_msg};
            size_t recv_bytes;
            size_t total_bytes;
            sock->receiveBytes(recv_buffer, ATMA::NETWORKMESSAGEBUFFERSIZE, recv_bytes);
            ATMA_ENGINE_TRACE("message received");
            total_bytes = recv_bytes;
            for(size_t i = 0; i < recv_bytes; i++)
            {
                msg->emplace_back(recv_buffer[i]);
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
                for(size_t i = 0; i < recv_bytes; i++)
                {
                    msg->emplace_back(recv_buffer[i]);
                }
            }
            sigs->m_recvMessage.release();
        },
        sigs,
        &wholeMessage
    );
    recvFuture.wait_for(3s);
    sendFuture.wait_for(3s);
    size_t cursor;
    ATMA::NetworkMessage nm = ATMA::NetworkSerde::deserialize(wholeMessage, cursor);
    EXPECT_EQ(nm.values().getAs<int>("port"), 4);
    delete sigs;
    delete ctx;
}

/**
 * Network manager host can receive message
 */
TEST_F(NetworkManagerFixture, NetworkManagerHostReceive)
{
    GTEST_SKIP();

    struct signals
    {
        const ATMA::URL address{"127.0.0.1"};
        const unsigned short port = 8899;
        std::binary_semaphore m_listenerUp{0}, m_recvConnStart{0}, m_sendConnStart{0}, m_sendMessage{0},
            m_recvMessage{0};
    };

    signals *sigs = new signals{};
    auto *ctx = makeContext();
    ctx->m_sysMan->addSystemType<NetworkSystem>(ctx, 0u);
    auto sys = ctx->m_sysMan->getSystem<NetworkSystem>(0u);
    ctx->m_attrMan->registerAttributeType<NetworkAttribute>(0u);
    auto objId = ctx->m_attrMan->createObject();
    ctx->m_attrMan->addAttribute(ctx, objId, 0u);
    ctx->m_netMan->addMessageListener(ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::CONNECTION_STARTED), sys);
    ctx->m_netMan->addMessageListener(ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::PORT_RESPONSE), sys);
    auto respAttr = ctx->m_attrMan->getAttribute<NetworkAttribute>(objId, 0u);
    auto sendFuture = std::async(
        std::launch::async,
        [](ATMA::ATMAContext *ctx, signals *sigs, std::shared_ptr<NetworkAttribute> attr)
        {
            ctx->m_netMan->startHosting(ctx, sigs->port);
            sigs->m_listenerUp.release();
            sigs->m_sendConnStart.acquire();
            // get conn id
            while(attr->m_connId == std::nullopt)
                ;
            ctx->m_netMan->stopHosting();

            // connection established
            sigs->m_recvConnStart.release();
            sigs->m_sendMessage.acquire();
            ctx->m_netMan->stopConnection(attr->m_connId);
        },
        ctx,
        sigs,
        respAttr
    );
    auto recvFuture = std::async(
        std::launch::async,
        [](signals *sigs)
        {
            sigs->m_listenerUp.acquire();
            auto sock = ATMA::Socket::makeSocket(sigs->address, sigs->port);
            sock->setBlocking(true);
            sigs->m_sendConnStart.release();
            sigs->m_recvConnStart.acquire();
            std::vector<unsigned char> sendingMessage = ATMA::NetworkSerde::serialize(
                ATMA::NetworkMessage{
                    ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::PORT_RESPONSE),
                    ATMA::Props{
                        {{"port",
                          std::pair<unsigned char, std::any>{
                              ATMA::NetworkMessageValueType(ATMA::NetworkMessageValueEnum::INT), 4
                          }}}

                    }
                }
            );
            std::span<unsigned char> send_buffer{sendingMessage};
            sock->sendBytes(send_buffer, sendingMessage.size());
            sigs->m_sendMessage.release();
        },
        sigs
    );
    recvFuture.wait_for(3s);
    sendFuture.wait_for(3s);
    EXPECT_EQ(
        respAttr->m_resps[ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::PORT_RESPONSE)].getAs<int>("port"), 4
    );
    delete sigs;
    delete ctx;
}
