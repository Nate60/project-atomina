#pragma once
#include "AtominaTest.hpp"

template<class T>
class ResourceFixture: public ::testing::Test
{
public:
    ATMA::ATMAContext &ctx = ATMA::ATMAContext::getContext();
protected:
    unsigned int registerResource(
        const unsigned int &l_resourceType,
        const std::optional<std::string> &l_filename = std::nullopt
    )
    {
        return ctx.registerResource(l_resourceType, l_filename);
    }

    std::shared_ptr<T> loadResource(const unsigned int &l_resourceID)
    {
        return ctx.loadResource<T>(l_resourceID);
    }

    void TearDown() override
    {
        ATMA_ENGINE_TRACE("starting teardown");
        ctx.purge();
    }
};

class UnTypedResourceFixture: public ::testing::Test
{
public:
    ATMA::ATMAContext &ctx = ATMA::ATMAContext::getContext();
protected:
    void TearDown() override
    {
        ctx.purge();
    }
};