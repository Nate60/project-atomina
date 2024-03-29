#include "ObjectEventSuite.hpp"
#include "event/ObjectEvent.hpp"

/**
 * Object events should be dispatched to any system that
 * has been registered to listen to that event type
 */
TEST_F(EventFixture, ObjectEventPassedToSystem)
{
    this->ctx.addSystemType<TestSystem>(0u);
    auto sys = this->ctx.getSystem<TestSystem>(0u);
    this->ctx.addObjectEventListener(0u, sys);
    auto id = this->ctx.createObject();
    this->ctx.registerAttributeType<TestAttribute>(0u);
    this->ctx.addAttribute(id, 0u);
    EXPECT_TRUE(this->ctx.hasAttribute(id, 0u));
    this->ctx.dispatchObjectEvent(ATMA::ObjectEventContext{0u});
    EXPECT_TRUE(this->ctx.getAttribute<TestAttribute>(id, 0u)->flag);
}

/**
 * Object events should be not be passed to a disabled system
 * even if it has been registered to listen to that event
 * type
 */
TEST_F(EventFixture, ObjectEventNotPassedToDisabledSystem)
{
    this->ctx.addSystemType<TestSystem>(0u);
    auto sys = this->ctx.getSystem<TestSystem>(0u);
    this->ctx.addObjectEventListener(0u, sys);
    auto id = this->ctx.createObject();
    this->ctx.registerAttributeType<TestAttribute>(0u);
    this->ctx.addAttribute(id, 0u);
    EXPECT_TRUE(this->ctx.hasAttribute(id, 0u));
    this->ctx.disableSystem(0u);
    this->ctx.dispatchObjectEvent(ATMA::ObjectEventContext{0u});
    EXPECT_FALSE(this->ctx.getAttribute<TestAttribute>(id, 0u)->flag);
}
