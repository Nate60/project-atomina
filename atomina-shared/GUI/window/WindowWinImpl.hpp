#ifdef _WINDOWS
#    pragma once
#    include "pch.hpp"
#    include "core/api.hpp"
#    include "GUI/AppWindow.hpp"
#    include "os/OSContextWinImpl.hpp"
#    include "util/Log.hpp"

namespace ATMA
{

    /**
     * Windows implementation of Application window using Xlib
     */
    class ATMA_API WindowWinImpl: public AppWindow
    {
    public:
        // Only constructor with default values to allow for default constructor
        // Specified the size and name of the window
        WindowWinImpl(
            const Vec2<int> &l_size = {180, 180},
            const std::string &l_name = "Atomina Application"
        );

        // default deconstructor
        virtual ~WindowWinImpl();

        /**
         * sets the size of the window to the new size
         * @param l_size new dimensions of the window
         */
        virtual void setSize(Vec2<int> l_size) override;

        /**
         * getter for window dimensions
         * @returns dimensions as a vector
         */
        virtual Vec2<int> getSize() override;

        /**
         * notify the window to show to the display
         */
        virtual void show() override;

        /**
         * get events that have been sent to the window and dispatch them
         */
        virtual void poll() override;

        /**
         * Swap the graphic buffers and bring the drawn buffer to the front
        */
        virtual void swapBuffers() override;

        /**
         * All Atomina AppWindows will have the same window class
         * creates the window class once and returns it for all future calls
         * @returns Windows Window Class for Atomina Applications
         */
        static WNDCLASS &getWindowClass()
        {
            static WNDCLASS windowClass; // Guaranteed to be destroyed.
                                         // Instantiated on first use.
            static std::once_flag flag;
            std::call_once(
                flag,
                [](WNDCLASS &l_wndClass)
                {
                    HINSTANCE hInstance = OSContextWinImpl::getContext().getDLLInstanceHandle();
                    l_wndClass.lpfnWndProc = WindowWinImpl::WindowProc;
                    l_wndClass.hInstance = hInstance;
                    l_wndClass.lpszClassName = "Atomina AppWindow Class";
                    RegisterClass(&l_wndClass);
                },
                windowClass
            );
            return windowClass;
        }
        friend class GLRenderContextOpenGLWinImpl;
    protected:
        static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
        HWND m_windowHandle;
    };

    const wchar_t DEFAULT_CLASS_NAME[] = {L"Atomina AppWindow Class"};

}
#else
#    error Windows implementation included in non-windows target
#endif