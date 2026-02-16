#pragma once
#include "AtominaTest.hpp"

/**
 * Fixture for testing Resource and helping with adding them
 * to the ATMA context
 */
template<class T>
class ResourceFixture: public ::testing::Test
{
public:
    ATMA::ATMAContext *m_ctx;
protected:
    /**
     * Adds resource to the ATMA contain with type of the template
     * class
     * @param l_resourceType id of the resource type
     * @param l_filename full qualified path to the resource
     * @returns unique identifier of the resource
     */
    unsigned int
    registerResource(const unsigned int &l_resourceType, const std::optional<std::string> &l_filename = std::nullopt)
    {
        return m_ctx->m_resMan->registerResource("", l_resourceType, l_filename);
    }

    /**
     * loads resource from file into memory
     * @param l_resourceID unique identifier of the resource
     * @returns pointer to loaded resource
     */
    std::shared_ptr<T> loadResource(const unsigned int &l_resourceID)
    {
        return m_ctx->m_resMan->loadResource<T>(m_ctx, l_resourceID);
    }

    /**
     * saves resource from file into memory
     * @param l_resourceID unique identifier of the resource
     * @returns pointer to loaded resource
     */
    void saveResource(const unsigned int &l_resourceID, const ATMA::Path &l_path)
    {
        return m_ctx->m_resMan->saveResource<T>(l_resourceID, l_path);
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
 * Fixture for type specific implementations of resources
 */
class UnTypedResourceFixture: public ::testing::Test
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
