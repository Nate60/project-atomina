#pragma once
#include "AtominaTest.hpp"

class EventFixture: public ::testing::Test
{
public:
    ATMA::ATMAContext &ctx = ATMA::ATMAContext::getContext();
protected:
    void TearDown() override;
};