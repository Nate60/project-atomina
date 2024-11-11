#ifndef ATMA_SERVER
#include "AtominaTestGame.hpp"

GameTest::GameTest() {}

GameTest::~GameTest() {}

void GameTest::setup(ATMA::ATMAContext &l_ctx)
{
    ATMA_ENGINE_INFO("Setting up test wrapper");
    l_ctx.purge();
    active = true;
}

void GameTest::update(ATMA::ATMAContext &l_ctx)
{
    ATMA_ENGINE_INFO("Test Wrapper is now running");
    ::testing::InitGoogleTest();
    auto result = RUN_ALL_TESTS();
    if(result > 0)
    {
        ATMA_ENGINE_ERROR("One or more tests have failed");
        active = false;
        exit(1);
    }
    else
    {
        ATMA_ENGINE_INFO("Tests passed successfully!");
    }
    active = false;
}

void GameTest::shutdown(ATMA::ATMAContext &l_ctx) {

}


std::unique_ptr<ATMA::Game>
ATMA::CreateGame()
{
    return std::unique_ptr<ATMA::Game>{new GameTest()};
}
#endif