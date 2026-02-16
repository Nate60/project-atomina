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
    ATMA::ATMAContext *m_ctx;
protected:
    /**
     * Helper function for adding system type of the template class
     * to the context
     * @param l_systemID id of the system type
     */
    void addSystemType(ATMA::ATMAContext *l_ctx, const unsigned int &l_systemID)
    {
        m_ctx->m_sysMan->addSystemType<T>(l_ctx, l_systemID);
    }

    void SetUp() override
    {
        m_ctx = makeContext();
    }

    /**
     * Cleans up context after each test
     */
    void TearDown() override
    {
        m_ctx->purge();
        destroyContext(m_ctx);
    }
};

/**
 * Test fixtured for type specific implemenations of systems
 */
class UntypedSystemFixture: public ::testing::Test
{
public:
    ATMA::ATMAContext *m_ctx;
protected:
    void SetUp() override
    {
        m_ctx = makeContext();
    }

    /**
     * Cleans up context after each test
     */
    void TearDown() override
    {
        m_ctx->purge();
        destroyContext(m_ctx);
    }
};
