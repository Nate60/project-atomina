#ifdef ATMA_SERVER
#    include "AtominaTestServer.hpp"

ServerTest::ServerTest() {}

ServerTest::~ServerTest() {}

void ServerTest::setup(ATMA::ATMAContext &l_ctx)
{
    ATMA_ENGINE_INFO("Setting up test wrapper");
    l_ctx.purge();
    active = true;
}

void ServerTest::update(ATMA::ATMAContext &l_ctx, const long long &l_dt)
{
    ATMA_ENGINE_INFO("Test Wrapper is now running");
    ATMA_ENGINE_INFO("Running Test Game with argc: {}", *l_ctx.argc);
    for(int i = 0; i < *l_ctx.argc; i++)
    {
        ATMA_ENGINE_INFO("Running with arg: {}", l_ctx.argv[i]);
    }
    ::testing::InitGoogleTest(l_ctx.argc, l_ctx.argv);
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

void ServerTest::shutdown(ATMA::ATMAContext &l_ctx) {}

std::unique_ptr<ATMA::Server> ATMA::CreateServer()
{
    return std::unique_ptr<ATMA::Server>{new ServerTest()};
}
#endif
