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
    std::function<void(ATMA::EventContext &)> clbck;
    if(failOnCallback)
        clbck = [&](ATMA::EventContext &eCtx) -> void
        { throw ATMA::ValueNotFoundException("test exception"); };
    else
        clbck = [&](ATMA::EventContext &eCtx) -> void { SUCCEED(); };
    if(ctx.hasSystem(0u))
        ctx.enableSystem(0u);
    ctx.addCallback(0u, getId(), clbck);
}

void
TestState::deactivate()
{
    ctx.removeCallback(0u, getId());
    if(ctx.hasSystem(0u))
        ctx.disableSystem(0u);
}

void
TestState::update(const sf::Time &l_time)
{
}

void
TestState::draw()
{
}