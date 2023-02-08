#include "pch.hpp"
#include "Window.hpp"

namespace ATMA
{

    Window::Window(const std::string &l_name): m_name(l_name) {}

    Window::Window(const Props &l_props, const std::string &l_name): m_name(l_name)
    {
        m_props = l_props;
    }

}