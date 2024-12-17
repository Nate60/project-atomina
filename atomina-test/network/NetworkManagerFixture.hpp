#pragma once

#include "AtominaTest.hpp"


class NetworkManagerFixture: public ::testing::Test
{
public:
    ATMA::ATMAContext &ctx = ATMA::ATMAContext::getContext();
protected:
};