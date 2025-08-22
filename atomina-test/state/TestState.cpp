#include "TestState.hpp"
#include "core/ATMAContext.hpp"

std::unordered_map<unsigned int, bool> TestState::m_flags{};

TestState::TestState(ATMA::ATMAContext *l_ctx): ATMA::BaseState(l_ctx), m_id(0) {}

TestState::TestState(ATMA::ATMAContext *l_ctx, const unsigned int &l_id): ATMA::BaseState(l_ctx), m_id(l_id)
{
    m_flags[m_id] = false;
}

TestState::~TestState() {}

void TestState::activate(ATMA::ATMAContext *l_ctx)
{
    if(l_ctx->m_sysMan->hasSystem(0u))
        l_ctx->m_sysMan->enableSystem(0u);
}

void TestState::deactivate(ATMA::ATMAContext *l_ctx)
{
    if(l_ctx->m_sysMan->hasSystem(0u))
        l_ctx->m_sysMan->disableSystem(0u);
}

void TestState::handleInput(ATMA::ATMAContext *l_ctx, const ATMA::WindowEvent &l_winEvent)
{
    m_flags[m_id] = true;
}
