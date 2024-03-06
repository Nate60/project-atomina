#ifdef _WINDOWS
#    include "pch.hpp"
#    include "WindowWinImpl.hpp"

namespace ATMA
{
    WindowWinImpl::WindowWinImpl(const Vec2<int> &l_size, const std::string &l_name):
        AppWindow(l_size, l_name)
    {

        ATMA_ENGINE_INFO("Creating Windows AppWindow with name: {0}", l_name);
        WNDCLASS l_windowClass = getWindowClass();
        m_windowHandle = CreateWindowEx(
            0,
            l_windowClass.lpszClassName,
            l_name.c_str(),
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            NULL,
            NULL,
            l_windowClass.hInstance,
            NULL
        );
    }

    WindowWinImpl::~WindowWinImpl() {}

    void WindowWinImpl::setSize(Vec2<int> l_size) {}

    Vec2<int> WindowWinImpl::getSize()
    {
        return Vec2<int>{};
    }

    void WindowWinImpl::show()
    {
        ShowWindow(m_windowHandle, SW_NORMAL);
    }

    void WindowWinImpl::poll() {}

    void WindowWinImpl::swapBuffers()
    {
        HDC hdc = GetDC(m_windowHandle);
        SwapBuffers(hdc);
    }

    // TODO: Handle window events and dispatch them
    LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

}
#else
#    error Windows implementation included in non-Windows target
#endif