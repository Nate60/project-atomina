#ifdef __linux__
#    include "pch.hpp"
#    include "WindowUnixImpl.hpp"

namespace ATMA
{

    WindowUnixImpl::WindowUnixImpl(const Vec2<int> &l_size, const std::string &l_name):
        AppWindow(l_size, l_name)
    {

        ATMA_ENGINE_INFO("Creating Unix AppWindow with name: {0}", l_name);

        m_display = XOpenDisplay(NULL);
        if(m_display == NULL)
        {
            ATMA_ENGINE_ERROR("Cannot open display when trying to create window");
        }
        m_screen = XDefaultScreen(m_display);

        m_window = XCreateSimpleWindow(
            m_display,
            RootWindow(m_display, m_screen),
            0,
            0,
            l_size.x,
            l_size.y,
            1,
            BlackPixel(m_display, m_screen),
            WhitePixel(m_display, m_screen)
        );

        /* process window close event through event handler so XNextEvent does not fail */
        Atom del_window = XInternAtom(m_display, "WM_DELETE_WINDOW", 0);
        XSetWMProtocols(m_display, m_window, &del_window, 1);

        /* select kind of events we are interested in */
        XSelectInput(m_display, m_window, ExposureMask | KeyPressMask);
    }

    WindowUnixImpl::~WindowUnixImpl()
    {
        ATMA_ENGINE_INFO("Destroying Unix Window {0}", m_name);
        /* destroy window */
        XDestroyWindow(m_display, m_window);
    }

    void WindowUnixImpl::setSize(Vec2<int> l_size) {}

    Vec2<int> WindowUnixImpl::getSize()
    {
        return Vec2<int>{};
    }

    void WindowUnixImpl::show()
    {
        /* display the window */
        XMapWindow(m_display, m_window);
    }

    void WindowUnixImpl::poll()
    {
        XEvent event;
        XNextEvent(m_display, &event);

        switch(event.type)
        {
        case KeyPress:
            /* FALLTHROUGH */
        case ClientMessage:
            ATMA_ENGINE_INFO("Got Client Message");
            /* destroy window */
            m_closed = true;
        case Expose:
            /* draw the window */
            XFillRectangle(
                m_display, m_window, DefaultGC(m_display, m_screen), 0, 0, m_size.x, m_size.y
            );

            /* NO DEFAULT */
        }
    }

}
#else
#    error Linux implementation included in non-Linux target
#endif