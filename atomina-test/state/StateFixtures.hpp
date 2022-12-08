#pragma once
#include "AtominaTest.hpp"
#include "TestState.hpp"

class TestState;

/**
 * Fixture for testing State implementations
 */
class StateFixture: public ::testing::Test
{
public:
    ATMA::ATMAContext &ctx = ATMA::ATMAContext::getContext();
protected:
    /**
     * Cleans up context between states
     */
    void TearDown() override;
};
