#include "ObjectEventSuite.hpp"
#include "event/ObjectEvent.hpp"

/**
 * Object events should be dispatched to any system that
 * has been registered to listen to that event type
 */
TEST_F(EventFixture, ObjectEventPassedToSystem)
{
    this->ctx.m_sysMan->addSystemType<TestSystem>(0u);
    auto sys = this->ctx.m_sysMan->getSystem<TestSystem>(0u);
    this->ctx.m_eventMan->addObjectEventListener(0u, sys);
    auto id = this->ctx.m_attrMan->createObject(ctx);
    this->ctx.m_attrMan->registerAttributeType<TestAttribute>(0u);
    this->ctx.m_attrMan->addAttribute(ctx, id, 0u);
    EXPECT_TRUE(this->ctx.m_attrMan->hasAttribute(id, 0u));
    this->ctx.m_eventMan->dispatchObjectEvent(ATMA::ObjectEventContext{0u});
    EXPECT_TRUE(this->ctx.m_attrMan->getAttribute<TestAttribute>(id, 0u)->flag);
}

/**
 * Object events should be not be passed to a disabled system
 * even if it has been registered to listen to that event
 * type
 */
TEST_F(EventFixture, ObjectEventNotPassedToDisabledSystem)
{
    this->ctx.m_sysMan->addSystemType<TestSystem>(0u);
    auto sys = this->ctx.m_sysMan->getSystem<TestSystem>(0u);
    this->ctx.m_eventMan->addObjectEventListener(0u, sys);
    auto id = this->ctx.m_attrMan->createObject(ctx);
    this->ctx.m_attrMan->registerAttributeType<TestAttribute>(0u);
    this->ctx.m_attrMan->addAttribute(ctx, id, 0u);
    EXPECT_TRUE(this->ctx.m_attrMan->hasAttribute(id, 0u));
    this->ctx.m_sysMan->disableSystem(0u);
    this->ctx.m_eventMan->dispatchObjectEvent(ATMA::ObjectEventContext{0u});
    EXPECT_FALSE(this->ctx.m_attrMan->getAttribute<TestAttribute>(id, 0u)->flag);
}
