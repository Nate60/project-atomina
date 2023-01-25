#include "pch.hpp"
#include "DummyState.hpp"

namespace ATMA
{
    DummyState::DummyState(): BaseState() {}

    DummyState::~DummyState() {}

    void DummyState::onCreate() {}

    void DummyState::onDestroy() {}

    void DummyState::activate() {}

    void DummyState::deactivate() {}

}