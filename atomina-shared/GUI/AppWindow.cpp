#include "pch.hpp"
#include "AppWindow.hpp"
#ifdef _WINDOWS
#    include "GUI/window/WindowWinImpl.hpp"
#    define __ATMAMAKEWINDOW() return std::make_shared<WindowWinImpl>()
#elif __linux__
#    include "GUI/window/WindowUnixImpl.hpp"
#    define __ATMAMAKEWINDOW() return std::make_shared<WindowUnixImpl>()
#endif

namespace ATMA
{
    AppWindow::AppWindow(const Vec2<int> &l_size, const std::string &l_name)
    {
        m_size = l_size;
        m_name = l_name;
        m_closed = false;
    }

    AppWindow::~AppWindow() {
        ATMA_ENGINE_INFO("Destroying App Window {0}", m_name);
    }

    std::string_view AppWindow::getName(){
        return std::string_view{m_name};
    }

    bool AppWindow::shouldClose(){
        return m_closed;
    }

    std::shared_ptr<AppWindow> AppWindow::makeWindow()
    {
        __ATMAMAKEWINDOW();
    }
}