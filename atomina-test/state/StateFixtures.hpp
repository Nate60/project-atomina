#pragma once
#include "TestState.hpp"
#include "../AtominaTest.hpp"


class TestState;
class StateFixture : public ::testing::Test
{
public:
    ATMA::ATMAContext &ctx = ATMA::ATMAContext::getContext();
protected:

    void TearDown() override;

};
