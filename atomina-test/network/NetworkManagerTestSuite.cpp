#include "NetworkManagerTestSuite.hpp"
#include "OAS/TestSystem.hpp"
#include "OAS/TestAttribute.hpp"

using namespace std::string_literals;

/**
 * Network manager should connect, listen, and disconnect
 */
TEST_F(NetworkManagerFixture, CanConnect)
{
    this->ctx.netManager.startHosting(4734);
    this->ctx.netManager.startConnection(ATMA::URL{"127.0.0.1"}, 4734);
    this->ctx.netManager.stopConnection();
    this->ctx.netManager.stopConnection(0u);
    this->ctx.netManager.stopHosting();
}

/**
 * Network manager can send as client
 */
TEST_F(NetworkManagerFixture, CanReceiveNetworkEvent)
{
    this->ctx.addSystemType<TestSystem>(0u);
    auto sys = this->ctx.getSystem<TestSystem>(0u);
    this->ctx.netManager.addMessageListener(ATMA::NetworkMessageType(ATMA::NetworkMessageEnum::CONNECTION_STARTED),sys);
    auto id = this->ctx.createObject();
    this->ctx.registerAttributeType<TestAttribute>(0u);
    this->ctx.addAttribute(id, 0u);
    this->ctx.netManager.startHosting(4734);
    this->ctx.netManager.startConnection(ATMA::URL{"127.0.0.1"}, 4734);
    this->ctx.netManager.stopConnection();
    this->ctx.netManager.stopConnection(1u);
    this->ctx.netManager.stopHosting();
    EXPECT_TRUE(this->ctx.getAttribute<TestAttribute>(id, 0u)->flag);
}