#include "GameTestSuite.hpp"

/**
 * Test to simply check if google test & atomina-shared has
 * been properly configured
 */
TEST(HelloWorld, canlog)
{
    ATMA_ENGINE_INFO("CAN LOG!!");
}
