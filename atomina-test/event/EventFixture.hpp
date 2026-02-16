#pragma once
#include "AtominaTest.hpp"

/**
 * Test Fixture for testing both window and object events
 */
class EventFixture: public ::testing::Test
{
public:
    ATMA::ATMAContext *m_ctx;
protected:
    /**
     * Inherited test function run after each test
     */
    void SetUp() override;

    /**
     * Inherited test function run after each test
     */
    void TearDown() override;
};
