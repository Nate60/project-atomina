#include "ResourceTestSuite.hpp"
#include <gtest/gtest.h>

TYPED_TEST_SUITE(ResourceFixture, ResourceTypes);

TYPED_TEST(ResourceFixture, CanRegisterResource)
{
    auto &ctx = this->ctx;
    auto id = this->registerResource(0u);
    EXPECT_TRUE(ctx.hasResource(id));
}

TYPED_TEST(ResourceFixture, CanLoadResource)
{
    auto &ctx = this->ctx;
    auto id = this->registerResource(0u);
    auto res = this->loadResource(id);
    EXPECT_NE(res, nullptr);
}

TYPED_TEST(ResourceFixture, CanUnloadResource)
{
    auto &ctx = this->ctx;
    auto id = this->registerResource(0u);
    auto res = this->loadResource(id);
    ctx.unloadResource(id);
    EXPECT_FALSE(ctx.hasLoadedResource(id));
}

TYPED_TEST(ResourceFixture, reloadingALoadedResourceReturnsResource)
{

    auto &ctx = this->ctx;
    ATMA_ENGINE_INFO("loaded context");
    auto id = this->registerResource(0u);
    ATMA_ENGINE_INFO("resource registered");
    auto res = this->loadResource(id);
    ATMA_ENGINE_INFO("resource loaded");
    auto res2 = this->loadResource(id);
    ATMA_ENGINE_INFO("resource loaded a second time");
    EXPECT_EQ(res, res2);

}

TYPED_TEST(ResourceFixture, CanRemoveResource)
{
    auto &ctx = this->ctx;
    auto id = this->registerResource(0u);
    ctx.removeResource(id);
    EXPECT_FALSE(ctx.hasResource(id));
}

TYPED_TEST(ResourceFixture, RemovingResourceUnloadsIt)
{
    auto &ctx = this->ctx;
    ATMA_ENGINE_INFO("loaded context");
    auto id = this->registerResource(0u);
    ATMA_ENGINE_INFO("registered resource");
    auto res = this->loadResource(id);
    ATMA_ENGINE_INFO("loaded resource");
    ctx.removeResource(id);
    ATMA_ENGINE_INFO("removed resource");
    EXPECT_FALSE(ctx.hasLoadedResource(id));

}
