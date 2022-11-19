#include "pch.hpp"
#include "BaseState.hpp"
#include "util/Log.hpp"

namespace ATMA
{

    BaseState::BaseState():
        m_active(false),
        m_communicable(false),
        m_transcendent(false),
        m_transparent(false)
    {
    }

    BaseState::BaseState(BaseState &&b) noexcept:
        m_communicable(b.m_communicable),
        m_transcendent(b.m_transcendent),
        m_transparent(b.m_transparent),
        m_view(b.m_view)
    {
    }

    BaseState::~BaseState() {}

    void BaseState::activate()
    {
        m_active = true;
    }

    void BaseState::deactivate()
    {
        m_active = false;
    }

    void BaseState::handleEvent(const WindowEvent &l_e)
    {
        ATMA_ENGINE_WARN("Base State handleEvent was called");
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

    sf::View &BaseState::getView()
    {
        return m_view;
    }

}