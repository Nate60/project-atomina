#pragma once
#include "AtominaTest.hpp"

template<class T>
class SystemFixture: public ::testing::Test
{
public:
    ATMA::ATMAContext &ctx = ATMA::ATMAContext::getContext();
protected:
    void addSystemType(const unsigned int &l_systemID)
    {
        ctx.addSystemType<T>(l_systemID);
    }

    void TearDown() override
    {
        ctx.purge();
    }
};

class UntypedSystemFixture: public ::testing::Test
{
public:
    ATMA::ATMAContext &ctx = ATMA::ATMAContext::getContext();
protected:
    void TearDown() override
    {
        ctx.purge();
    }
};
