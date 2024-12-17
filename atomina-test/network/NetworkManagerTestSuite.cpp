#include "NetworkManagerTestSuite.hpp"

using namespace std::string_literals;

/**
 * Network message should serialize
 */
TEST_F(NetworkManagerFixture, CanConnect)
{
    this->ctx.netManager.startHosting(4734);
    this->ctx.netManager.startConnection(ATMA::URL{"127.0.0.1"}, 4734);
    this->ctx.netManager.stopConnection();
    this->ctx.netManager.stopHosting();
    ATMA_ENGINE_INFO("ending networkmanager test");
}