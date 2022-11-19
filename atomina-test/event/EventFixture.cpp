#include "EventFixture.hpp"

void
EventFixture::TearDown()
{
    ctx.purge();
}