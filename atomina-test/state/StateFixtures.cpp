#include "StateFixtures.hpp"

void StateFixture::SetUp()
{

    m_ctx = makeContext();
}

/**
 * Cleans up context after each test
 */
void StateFixture::TearDown()
{
    m_ctx->purge();
    destroyContext(m_ctx);
}
