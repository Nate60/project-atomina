#include "ObjectEventSuite.hpp"
#include "event/ObjectEvent.hpp"

/**
 * Object events should be dispatched to any system that
 * has been registered to listen to that event type
 */
TEST_F(EventFixture, ObjectEventPassedToSystem)
{
    this->m_ctx->m_sysMan->addSystemType<TestSystem>(this->m_ctx, 0u);
    auto sys = this->m_ctx->m_sysMan->getSystem<TestSystem>(0u);
    this->m_ctx->m_eventMan->addObjectEventListener(0u, sys);
    auto id = this->m_ctx->m_attrMan->createObject();
    this->m_ctx->m_attrMan->registerAttributeType<TestAttribute>(0u);
    this->m_ctx->m_attrMan->addAttribute(m_ctx, id, 0u);
    EXPECT_TRUE(this->m_ctx->m_attrMan->hasAttribute(id, 0u));
    this->m_ctx->m_eventMan->dispatchObjectEvent(this->m_ctx, ATMA::ObjectEventContext{0u});
    EXPECT_TRUE(this->m_ctx->m_attrMan->getAttribute<TestAttribute>(id, 0u)->flag);
}

/**
 * Object events should be not be passed to a disabled system
 * even if it has been registered to listen to that event
 * type
 */
TEST_F(EventFixture, ObjectEventNotPassedToDisabledSystem)
{
    this->m_ctx->m_sysMan->addSystemType<TestSystem>(this->m_ctx, 0u);
    auto sys = this->m_ctx->m_sysMan->getSystem<TestSystem>(0u);
    this->m_ctx->m_eventMan->addObjectEventListener(0u, sys);
    auto id = this->m_ctx->m_attrMan->createObject();
    this->m_ctx->m_attrMan->registerAttributeType<TestAttribute>(0u);
    this->m_ctx->m_attrMan->addAttribute(m_ctx, id, 0u);
    EXPECT_TRUE(this->m_ctx->m_attrMan->hasAttribute(id, 0u));
    this->m_ctx->m_sysMan->disableSystem(0u);
    this->m_ctx->m_eventMan->dispatchObjectEvent(this->m_ctx, ATMA::ObjectEventContext{0u});
    EXPECT_FALSE(this->m_ctx->m_attrMan->getAttribute<TestAttribute>(id, 0u)->flag);
}
