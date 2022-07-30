#pragma once
#include "../AtominaTest.hpp"
#include <gtest/gtest.h>

template <class T>
class SystemFixture : public ::testing::Test
{
public:
    ATMA::ATMAContext &ctx = ATMA::ATMAContext::getContext();
protected:


    void TearDown() override
    {
        auto &ctx = ATMA::ATMAContext::getContext();
        ctx.purge();
    }

};

class UntypedSystemFixture : public ::testing::Test
{
public:
    ATMA::ATMAContext &ctx = ATMA::ATMAContext::getContext();
protected:


    void TearDown() override
    {
        auto &ctx = ATMA::ATMAContext::getContext();
        ctx.purge();
    }

};
