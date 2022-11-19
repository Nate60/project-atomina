#include "pch.hpp"
#include "WindowEvent.hpp"

namespace ATMA
{

    WindowEvent::WindowEvent() {}

    WindowEvent::WindowEvent(sf::Event &l_e): m_event(l_e) {}

    WindowEvent::~WindowEvent() {}

}