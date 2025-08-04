#include "SystemTestSuite.hpp"
#include "TestSystem.hpp"

TYPED_TEST_SUITE(SystemFixture, SystemTypes);

/**
 * should be able to add a system to the context
 */
TYPED_TEST(SystemFixture, AddSystem)
{
    unsigned int sysType = TypeParam{}.getType();
    this->addSystemType(sysType);
    EXPECT_TRUE(this->ctx.m_sysMan->hasSystem(sysType));
}

/**
 * should not be able to add a system to the context when the context
 * already has a system assigned to that ID
 */
TYPED_TEST(SystemFixture, AddDuplicateSystem)
{
    unsigned int sysType = TypeParam{}.getType();
    TypeParam sys2{};
    this->addSystemType(sysType);
    EXPECT_THROW(this->addSystemType(sysType), ATMA::RegistrationException);
}

/**
 * Removing system should remove the system from the context
 */
TYPED_TEST(SystemFixture, RemoveSystem)
{
    unsigned int sysType = TypeParam{}.getType();
    this->addSystemType(sysType);
    this->ctx.m_sysMan->removeSystem(sysType);
    EXPECT_FALSE(this->ctx.m_sysMan->hasSystem(sysType));
}

/**
 * Removing a system that has not been registered in the context
 * should throw an exception
 */
TYPED_TEST(SystemFixture, RemoveNonExistentSystem)
{
    EXPECT_THROW(this->ctx.m_sysMan->removeSystem(0u), ATMA::ValueNotFoundException);
}

/**
 * disabling a system should prevent it from updating any attributes
 */
TEST_F(UntypedSystemFixture, DisableSystem)
{
    unsigned int sysType = TestSystem{}.getType();
    ctx.m_attrMan->registerAttributeType<TestAttribute>(0u);
    ctx.m_sysMan->addSystemType<TestSystem>(sysType);
    auto obj = ctx.m_attrMan->createObject(ctx);
    ctx.m_attrMan->addAttribute(ctx, obj, 0u);
    ctx.m_sysMan->disableSystem(sysType);
    ctx.m_sysMan->update(ctx, 0LL);
    EXPECT_FALSE(ctx.m_attrMan->getAttribute<TestAttribute>(obj, 0u)->flag);
}

/**
 * Adding an attribute that matches an existing system should update the
 * atttribute
 */
TEST_F(UntypedSystemFixture, AddAttributeAddsToSystem)
{
    unsigned int sysType = TestSystem{}.getType();
    this->ctx.m_attrMan->registerAttributeType<TestAttribute>(0u);
    this->ctx.m_sysMan->addSystemType<TestSystem>(sysType);
    auto obj = this->ctx.m_attrMan->createObject(ctx);
    this->ctx.m_attrMan->addAttribute(ctx, obj, 0u);
    this->ctx.m_sysMan->update(ctx, 0LL);
    EXPECT_TRUE(this->ctx.m_attrMan->getAttribute<TestAttribute>(obj, 0u)->flag);
}

/**
 * Adding an attribute and updating a system with that attribute as a requirement
 * should update the attribute
 */
TEST_F(UntypedSystemFixture, AddSystemThatMatchesAttributeShouldUpdateIt)
{
    unsigned int sysType = TestSystem{}.getType();
    this->ctx.m_attrMan->registerAttributeType<TestAttribute>(0u);
    auto obj = this->ctx.m_attrMan->createObject(ctx);
    this->ctx.m_attrMan->addAttribute(ctx, obj, 0u);
    this->ctx.m_sysMan->addSystemType<TestSystem>(sysType);
    this->ctx.m_sysMan->update(ctx, 0LL);
    EXPECT_TRUE(this->ctx.m_attrMan->getAttribute<TestAttribute>(obj, 0u)->flag);
}
