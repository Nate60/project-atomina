#include "SystemTestSuite.hpp"
#include "TestSystem.hpp"
#include "core/ATMAContext.hpp"
#include "event/EventContext.hpp"
#include "util/AtominaException.hpp"
#include <functional>
#include <memory>

TYPED_TEST_SUITE(SystemFixture, SystemTypes);

//should be able to add a system to the context
TYPED_TEST(SystemFixture, AddSystem)
{
    TypeParam sys{};
    this->ctx.addSystem(sys.getType(), std::make_unique<TypeParam>(sys));
    EXPECT_TRUE(this->ctx.hasSystem(sys.getType()));
}

//should not be able to add a system to the context when the context
//already has a system assigned to that ID
TYPED_TEST(SystemFixture, AddDuplicateSystem)
{
    TypeParam sys{};
    TypeParam sys2{};
    this->ctx.addSystem(sys.getType(), std::make_unique<TypeParam>(sys));
    EXPECT_THROW(this->ctx.addSystem(sys.getType(), std::make_unique<TypeParam>(sys)), ATMA::RegistrationException);
}

//Removing system should remove the system from the context
TYPED_TEST(SystemFixture, RemoveSystem)
{
    TypeParam sys{};
    auto sysType = sys.getType();
    this->ctx.addSystem(sysType, std::make_unique<TypeParam>(sys));
    this->ctx.removeSystem(sysType);
    EXPECT_FALSE(this->ctx.hasSystem(sys.getType()));
}

//Removing a system that has not been registered in the context
//should throw an exception
TYPED_TEST(SystemFixture, RemoveNonExistentSystem)
{
    EXPECT_THROW(this->ctx.removeSystem(0u), ATMA::ValueNotFoundException);
}

TEST_F(UntypedSystemFixture, CanAddSystemFunctionAsCallback)
{
    std::unique_ptr<TestSystem> sys{new TestSystem{}};
    auto sysType = sys->getType();
    auto &ctx = ATMA::ATMAContext::getContext();
    std::function<void(ATMA::EventContext&)> f = std::bind(&TestSystem::doSomething, *sys, std::placeholders::_1);
    ctx.addCallback(0u,0u, f);
    ctx.addSystem(sysType, std::move(sys));
    ctx.addEvent(0u, 0u, ATMA::EventContext{});
    EXPECT_THROW(ctx.update(), ATMA::ValueNotFoundException);
}

//disabling a system should prevent it from updating any attributes
TEST_F(UntypedSystemFixture, DisableSystem)
{
    TestSystem sys{};
    auto sysType = sys.getType();
    auto &ctx = ATMA::ATMAContext::getContext();
    ctx.registerAttributeType<TestAttribute>(0u);
    ctx.addSystem(sysType, std::make_unique<TestSystem>(sys));
    auto obj = ctx.createObject();
    ctx.addAttribute(obj, 0u);
    ctx.disableSystem(sysType);
    ctx.update();
    EXPECT_FALSE(ctx.getAttribute<TestAttribute>(obj, 0u)->flag);
}

//Adding an attribute that matches an existing system should update the
//atttribute
TEST_F(UntypedSystemFixture, AddAttributeAddsToSystem)
{
    TestSystem sys{};
    auto sysType = sys.getType();
    this->ctx.registerAttributeType<TestAttribute>(0u);
    this->ctx.addSystem(sysType, std::make_unique<TestSystem>(sys));
    auto obj = this->ctx.createObject();
    this->ctx.addAttribute(obj, 0u);
    this->ctx.update();
    EXPECT_TRUE(this->ctx.getAttribute<TestAttribute>(obj, 0u)->flag);
}

TEST_F(UntypedSystemFixture, AddSystemThatMatchesAttributeShouldUpdateIt)
{
    TestSystem sys{};
    auto sysType = sys.getType();
    this->ctx.registerAttributeType<TestAttribute>(0u);
    auto obj = this->ctx.createObject();
    this->ctx.addAttribute(obj, 0u);
    this->ctx.addSystem(sysType, std::make_unique<TestSystem>(sys));
    this->ctx.update();
    EXPECT_TRUE(this->ctx.getAttribute<TestAttribute>(obj, 0u)->flag);
}
