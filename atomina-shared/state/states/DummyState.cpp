#include "pch.hpp"
#include "DummyState.hpp"

namespace ATMA
{
    DummyState::DummyState(ATMAContext *l_ctx): BaseState(l_ctx) {}

    DummyState::~DummyState() {}

    void DummyState::activate(ATMAContext *l_ctx) {}

    void DummyState::deactivate(ATMAContext *l_ctx) {}

}
