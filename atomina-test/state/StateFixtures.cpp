#include "StateFixtures.hpp"

void
StateFixture::TearDown()
{
    ctx.purge();
}