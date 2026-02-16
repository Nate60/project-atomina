#include "pch.hpp"
#include "BaseState.hpp"
#include "util/Log.hpp"

namespace ATMA
{

    BaseState::BaseState(ATMAContext *l_ctx):
        m_active(false),
        m_transparent(false),
        m_transcendent(false),
        m_communicable(false)
    {
    }

    BaseState::BaseState(BaseState &&b) noexcept:
        m_active(b.m_active),
        m_transparent(b.m_transparent),
        m_transcendent(b.m_transcendent),
        m_communicable(b.m_communicable)
    {
    }

    BaseState::~BaseState() {}

    void BaseState::activate(ATMAContext *l_ctx)
    {
        m_active = true;
    }

    void BaseState::deactivate(ATMAContext *l_ctx)
    {
        m_active = false;
    }

    bool BaseState::operator==(const BaseState &b) const
    {
        return this->getId() == b.getId();
    }

    bool BaseState::operator<(const BaseState &b) const
    {
        return this->getId() < b.getId();
    }

    bool BaseState::operator>(const BaseState &b) const
    {
        return this->getId() > b.getId();
    }

}
