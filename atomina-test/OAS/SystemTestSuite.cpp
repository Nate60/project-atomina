#include "SystemTestSuite.hpp"

TYPED_TEST_SUITE(SystemFixture, SystemTypes);

// should be able to add a system to the context
TYPED_TEST(SystemFixture, AddSystem)
{
    unsigned int sysType = TypeParam{}.getType();
    this->addSystemType(sysType);
    EXPECT_TRUE(this->ctx.hasSystem(sysType));
}

// should not be able to add a system to the context when the context
// already has a system assigned to that ID
TYPED_TEST(SystemFixture, AddDuplicateSystem)
{
    unsigned int sysType = TypeParam{}.getType();
    TypeParam sys2{};
    this->addSystemType(sysType);
    EXPECT_THROW(this->addSystemType(sysType), ATMA::RegistrationException);
}

// Removing system should remove the system from the context
TYPED_TEST(SystemFixture, RemoveSystem)
{
    unsigned int sysType = TypeParam{}.getType();
    this->addSystemType(sysType);
    this->ctx.removeSystem(sysType);
    EXPECT_FALSE(this->ctx.hasSystem(sysType));
}

// Removing a system that has not been registered in the context
// should throw an exception
TYPED_TEST(SystemFixture, RemoveNonExistentSystem)
{
    EXPECT_THROW(this->ctx.removeSystem(0u), ATMA::ValueNotFoundException);
}

TEST_F(UntypedSystemFixture, CanAddSystemFunctionAsCallback)
{
    unsigned int sysType = TestSystem{}.getType();
    auto &ctx = ATMA::ATMAContext::getContext();
    ctx.addSystemType<TestSystem>(sysType);
    auto sys = ctx.getSystem<TestSystem>(sysType);
    std::function<void(ATMA::EventContext &)> f =
        std::bind(&TestSystem::doSomething, *sys, std::placeholders::_1);
    ctx.addCallback(0u, 0u, f);
    ctx.addEvent(0u, 0u, ATMA::EventContext{});

    EXPECT_THROW(ctx.update(), ATMA::ValueNotFoundException);
}

// disabling a system should prevent it from updating any attributes
TEST_F(UntypedSystemFixture, DisableSystem)
{
    unsigned int sysType = TestSystem{}.getType();
    auto &ctx = ATMA::ATMAContext::getContext();
    ctx.registerAttributeType<TestAttribute>(0u);
    ctx.addSystemType<TestSystem>(sysType);
    auto obj = ctx.createObject();
    ctx.addAttribute(obj, 0u);
    ctx.disableSystem(sysType);
    ctx.update();
    EXPECT_FALSE(ctx.getAttribute<TestAttribute>(obj, 0u)->flag);
}

// Adding an attribute that matches an existing system should update the
// atttribute
TEST_F(UntypedSystemFixture, AddAttributeAddsToSystem)
{
    unsigned int sysType = TestSystem{}.getType();
    this->ctx.registerAttributeType<TestAttribute>(0u);
    this->ctx.addSystemType<TestSystem>(sysType);
    auto obj = this->ctx.createObject();
    this->ctx.addAttribute(obj, 0u);
    this->ctx.update();
    EXPECT_TRUE(this->ctx.getAttribute<TestAttribute>(obj, 0u)->flag);
}

TEST_F(UntypedSystemFixture, AddSystemThatMatchesAttributeShouldUpdateIt)
{
    unsigned int sysType = TestSystem{}.getType();
    this->ctx.registerAttributeType<TestAttribute>(0u);
    auto obj = this->ctx.createObject();
    this->ctx.addAttribute(obj, 0u);
    this->ctx.addSystemType<TestSystem>(sysType);
    this->ctx.update();
    EXPECT_TRUE(this->ctx.getAttribute<TestAttribute>(obj, 0u)->flag);
}
