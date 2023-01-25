#include "TestState.hpp"

TestState::TestState(): ATMA::BaseState() {}

TestState::~TestState() {}

void
TestState::onCreate()
{
}

void
TestState::onDestroy()
{
}

void
TestState::activate()
{
    if(ctx.hasSystem(0u))
        ctx.enableSystem(0u);
}

void
TestState::deactivate()
{
    if(ctx.hasSystem(0u))
        ctx.disableSystem(0u);
}
