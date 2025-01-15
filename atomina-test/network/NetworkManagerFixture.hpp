#pragma once

#include "AtominaTest.hpp"


class NetworkManagerFixture: public ::testing::Test
{
public:
    ATMA::ATMAContext &ctx = ATMA::ATMAContext::getContext();
protected:

    void SetUp() override
    {
    }

    void TearDown() override
    {
        this->ctx.netManager.stopHosting();
        this->ctx.purge();
    }

};