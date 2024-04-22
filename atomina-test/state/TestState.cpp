#include "TestState.hpp"

std::unordered_map<unsigned int, bool> TestState::m_flags{};

TestState::TestState(): ATMA::BaseState(), m_id(0) {}

TestState::TestState(const unsigned int &l_id):
    ATMA::BaseState(),
    m_id(l_id)
{
    m_flags[m_id] = false;
}

TestState::~TestState() {}

void TestState::activate()
{
    if(ctx.hasSystem(0u))
        ctx.enableSystem(0u);
}

void TestState::deactivate()
{
    if(ctx.hasSystem(0u))
        ctx.disableSystem(0u);
}

void TestState::handleInput(const ATMA::WindowEvent &l_winEvent)
{
    m_flags[m_id] = true;
}