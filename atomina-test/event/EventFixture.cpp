#include "EventFixture.hpp"
#include "core/ATMAContext.hpp"

void EventFixture::SetUp()
{
    m_ctx = makeContext();
}

void EventFixture::TearDown()
{
    m_ctx->purge();
    destroyContext(m_ctx);
}
