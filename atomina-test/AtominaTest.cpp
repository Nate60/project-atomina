#include "AtominaTest.hpp"

GameTest::GameTest() {}

GameTest::~GameTest() {}

void
GameTest::run()
{
    ATMA_ENGINE_INFO("Test Wrapper is now running");
    active = true;
    ::testing::InitGoogleTest();
    auto result = RUN_ALL_TESTS();
    if(result > 0)
    {
        ATMA_ENGINE_ERROR("One or more tests have failed");
        exit(1);
    }
    else
    {
        ATMA_ENGINE_INFO("Tests passed successfully!");
    }
}

void
GameTest::shutdown()
{
    active = false;
}


#ifdef _WINDOWS
int
main()
{
    ATMA::startGame(std::unique_ptr<ATMA::Game>{new GameTest{}});
}
#else
std::unique_ptr<ATMA::Game>
ATMA::CreateGame()
{
    return std::unique_ptr<ATMA::Game>{new GameTest()};
}
#endif