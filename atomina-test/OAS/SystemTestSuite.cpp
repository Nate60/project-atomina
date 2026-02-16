#include "SystemTestSuite.hpp"
#include "TestSystem.hpp"

TYPED_TEST_SUITE(SystemFixture, SystemTypes);

/**
 * should be able to add a system to the context
 */
TYPED_TEST(SystemFixture, AddSystem)
{
    unsigned int sysType = TypeParam{}.getType();
    this->addSystemType(this->m_ctx, sysType);
    EXPECT_TRUE(this->m_ctx->m_sysMan->hasSystem(sysType));
}

/**
 * should not be able to add a system to the context when the context
 * already has a system assigned to that ID
 */
TYPED_TEST(SystemFixture, AddDuplicateSystem)
{
    unsigned int sysType = TypeParam{}.getType();
    TypeParam sys2{};
    this->addSystemType(this->m_ctx, sysType);
    EXPECT_THROW(this->addSystemType(this->m_ctx, sysType), ATMA::RegistrationException);
}

/**
 * Removing system should remove the system from the context
 */
TYPED_TEST(SystemFixture, RemoveSystem)
{
    unsigned int sysType = TypeParam{}.getType();
    this->addSystemType(this->m_ctx, sysType);
    this->m_ctx->m_sysMan->removeSystem(sysType);
    EXPECT_FALSE(this->m_ctx->m_sysMan->hasSystem(sysType));
}

/**
 * Removing a system that has not been registered in the context
 * should throw an exception
 */
TYPED_TEST(SystemFixture, RemoveNonExistentSystem)
{
    EXPECT_THROW(this->m_ctx->m_sysMan->removeSystem(0u), ATMA::ValueNotFoundException);
}

/**
 * disabling a system should prevent it from updating any attributes
 */
TEST_F(UntypedSystemFixture, DisableSystem)
{
    unsigned int sysType = TestSystem{}.getType();
    m_ctx->m_attrMan->registerAttributeType<TestAttribute>(0u);
    m_ctx->m_sysMan->addSystemType<TestSystem>(this->m_ctx, sysType);
    auto obj = m_ctx->m_attrMan->createObject();
    m_ctx->m_attrMan->addAttribute(m_ctx, obj, 0u);
    m_ctx->m_sysMan->disableSystem(sysType);
    m_ctx->m_sysMan->update(m_ctx, 0LL);
    EXPECT_FALSE(m_ctx->m_attrMan->getAttribute<TestAttribute>(obj, 0u)->flag);
}

/**
 * Adding an attribute that matches an existing system should update the
 * atttribute
 */
TEST_F(UntypedSystemFixture, AddAttributeAddsToSystem)
{
    unsigned int sysType = TestSystem{}.getType();
    this->m_ctx->m_attrMan->registerAttributeType<TestAttribute>(0u);
    this->m_ctx->m_sysMan->addSystemType<TestSystem>(this->m_ctx, sysType);
    auto obj = this->m_ctx->m_attrMan->createObject();
    this->m_ctx->m_attrMan->addAttribute(m_ctx, obj, 0u);
    this->m_ctx->m_sysMan->update(m_ctx, 0LL);
    EXPECT_TRUE(this->m_ctx->m_attrMan->getAttribute<TestAttribute>(obj, 0u)->flag);
}

/**
 * Adding an attribute and updating a system with that attribute as a requirement
 * should update the attribute
 */
TEST_F(UntypedSystemFixture, AddSystemThatMatchesAttributeShouldUpdateIt)
{
    unsigned int sysType = TestSystem{}.getType();
    this->m_ctx->m_attrMan->registerAttributeType<TestAttribute>(0u);
    auto obj = this->m_ctx->m_attrMan->createObject();
    this->m_ctx->m_attrMan->addAttribute(m_ctx, obj, 0u);
    this->m_ctx->m_sysMan->addSystemType<TestSystem>(this->m_ctx, sysType);
    this->m_ctx->m_sysMan->update(m_ctx, 0LL);
    EXPECT_TRUE(this->m_ctx->m_attrMan->getAttribute<TestAttribute>(obj, 0u)->flag);
}
