#include "pch.hpp"
#include "WindowEvent.hpp"

namespace ATMA
{

    WindowEvent::WindowEvent(AppWindow *l_win):
        m_win(l_win),
        m_type(WindowEventEnum::None),
        m_props{}
    {
        ATMA_ENGINE_TRACE("Creating Window Event");
    }

    WindowEvent::WindowEvent(AppWindow *l_win, const WindowEventEnum &l_type):
        m_win(l_win),
        m_type(l_type),
        m_props{}
    {
    }

    WindowEvent::WindowEvent(
        AppWindow *l_win,
        const WindowEventEnum &l_type,
        const Props &l_props
    ):
        m_win(l_win),
        m_type(l_type),
        m_props(l_props)
    {
    }

    WindowEvent::WindowEvent(const WindowEvent &l_other):
        m_win(l_other.m_win),
        m_type(l_other.m_type),
        m_props(l_other.m_props)
    {
    }

    WindowEvent::WindowEvent(WindowEvent &&l_other):
        m_win(std::move(l_other.m_win)),
        m_type(std::move(l_other.m_type)),
        m_props(std::move(l_other.m_props))
    {
    }

    WindowEvent::~WindowEvent() {}

}