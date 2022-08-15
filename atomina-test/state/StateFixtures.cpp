#include "StateFixtures.hpp"


    void StateFixture::TearDown()
    {
        auto &ctx = ATMA::ATMAContext::getContext();
        ctx.purge();
    }