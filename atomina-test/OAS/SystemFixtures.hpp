#pragma once
#include "AtominaTest.hpp"

/**
 * Test Fixture for running tests against systems of the Object
 * Attribute System
 */
template<class T>
class SystemFixture: public ::testing::Test
{
public:
    ATMA::ATMAContext &ctx = ATMA::ATMAContext::getContext();
protected:
    /**
     * Helper function for adding system type of the template class
     * to the context
     * @param l_systemID id of the system type
     */
    void addSystemType(const unsigned int &l_systemID)
    {
        ctx.addSystemType<T>(l_systemID);
    }

    /**
     * Clean up context after each test
     */
    void TearDown() override
    {
        ctx.purge();
    }
};

/**
 * Test fixtured for type specific implemenations of systems
 */
class UntypedSystemFixture: public ::testing::Test
{
public:
    ATMA::ATMAContext &ctx = ATMA::ATMAContext::getContext();
protected:
    /**
     * Cleans up the context after each test
     */
    void TearDown() override
    {
        ctx.purge();
    }
};
