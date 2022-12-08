#pragma once
#include "AtominaTest.hpp"

/**
 * Test Fixture for testing both window and object events
 */
class EventFixture: public ::testing::Test
{
public:
    ATMA::ATMAContext &ctx = ATMA::ATMAContext::getContext();
protected:
    /**
     * Inherited test function run after each test
     */
    void TearDown() override;
};