#ifdef _WINDOWS
#    include "pch.hpp"
#    include "WindowWinImpl.hpp"

namespace ATMA
{
    WindowWinImpl::WindowWinImpl(const Vec2<unsigned int> &l_size, const std::string &l_name):
        AppWindow(l_size, l_name)
    {

        ATMA_ENGINE_INFO("Creating Windows AppWindow with name: {0}", l_name);
        WNDCLASSEX l_windowClass = getWindowClass();
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
            (LPVOID)this
        );
        SetWindowLongPtr(m_windowHandle, 0, (LONG_PTR)this);
    }

    WindowWinImpl::~WindowWinImpl() {}

    void WindowWinImpl::setSize(const Vec2<unsigned int> &l_size)
    {
        m_size = l_size;
    }

    void WindowWinImpl::show()
    {
        ShowWindow(m_windowHandle, SW_NORMAL);
    }

    void WindowWinImpl::poll()
    {
        MSG Msg;
        while(PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&Msg);
            DispatchMessage(&Msg);
        }
        UpdateWindow(m_windowHandle);
    }

    void WindowWinImpl::swapBuffers()
    {
        HDC hdc = GetDC(m_windowHandle);
        SwapBuffers(hdc);
    }

    LRESULT CALLBACK WindowWinImpl::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        WindowWinImpl *pWin = reinterpret_cast<WindowWinImpl *>(::GetWindowLongPtr(hwnd, 0));
        Props props{true};
        switch(uMsg)
        {
        case WM_KEYDOWN:
            props["keycode"] = (unsigned int)LOWORD(wParam);
            props["repeat"] = (boolean)((HIWORD(lParam) & KF_REPEAT) > 0);
            ATMAContext::getContext().dispatchWindowEvent(WindowEvent{
                pWin->shared_from_this(), WindowEventEnum::KeyDowned, std::move(props)});
            return 0;
        case WM_KEYUP:
            props["keycode"] = (unsigned int)wParam;
            props["repeat"] = false;
            ATMAContext::getContext().dispatchWindowEvent(WindowEvent{
                pWin->shared_from_this(), WindowEventEnum::KeyUpped, std::move(props)});
            return 0;
        case WM_SIZE:
            props["width"] = (unsigned int)LOWORD(lParam);
            props["height"] = (unsigned int)HIWORD(lParam);
            ATMAContext::getContext().dispatchWindowEvent(WindowEvent{
                pWin->shared_from_this(), WindowEventEnum::Resized, std::move(props)});
            return 0;
        case WM_CLOSE:
            ATMAContext::getContext().dispatchWindowEvent(WindowEvent{
                pWin->shared_from_this(), WindowEventEnum::Closed, std::move(props)});
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
        }
    }

}
#else
#    error Windows implementation included in non-Windows target
#endif