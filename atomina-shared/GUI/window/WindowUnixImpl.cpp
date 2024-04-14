#ifdef __linux__
#    include "pch.hpp"
#    include "WindowUnixImpl.hpp"
#    include "util/ATConst.hpp"

namespace ATMA
{

    WindowUnixImpl::WindowUnixImpl(const Vec2<unsigned int> &l_size, const std::string &l_name):
        AppWindow(l_size, l_name)
    {
        ATMA_ENGINE_INFO("Creating Unix AppWindow with name: {0}", l_name);

        m_display = getDisplay();
        m_screen = DefaultScreen(m_display);
        m_root = RootWindow(m_display, m_screen);
        if(m_display == NULL)
        {
            ATMA_ENGINE_ERROR("Cannot open display when trying to create window");
        }

        XVisualInfo *vi = glXGetVisualFromFBConfig(m_display, getFrameBufferConfig(m_display));
        XSetWindowAttributes swa;

        swa.colormap = m_colourMap = XCreateColormap(m_display, m_root, vi->visual, AllocNone);
        swa.background_pixmap = 0L;
        swa.border_pixel = 0;
        swa.event_mask = StructureNotifyMask;

        m_window = XCreateWindow(
            m_display,
            m_root,
            0,
            0,
            l_size.x,
            l_size.y,
            0,
            vi->depth,
            InputOutput,
            vi->visual,
            CWBorderPixel | CWColormap | CWEventMask,
            &swa
        );

        XFree(vi);

        XStoreName(m_display, m_window, l_name.c_str());

        /* process window close event through event handler so XNextEvent does not fail */
        m_deleteMessage = XInternAtom(m_display, "WM_DELETE_WINDOW", 0);
        XSetWMProtocols(m_display, m_window, &m_deleteMessage, 1);
        XSelectInput(m_display, m_window, WindowUnixImpl::EVENT_MASK);
    }

    WindowUnixImpl::~WindowUnixImpl()
    {
        ATMA_ENGINE_INFO("Destroying Unix Window {0}", m_name);
        /* destroy window */
        XDestroyWindow(m_display, m_window);
        XFreeColormap(m_display, m_colourMap);
    }

    void WindowUnixImpl::setSize(const Vec2<unsigned int> &l_size)
    {
        m_size.x = l_size.x;
        m_size.y = l_size.y;
        redraw();
    }

    void WindowUnixImpl::show()
    {
        /* display the window */
        XMapWindow(m_display, m_window);
    }

    void WindowUnixImpl::poll()
    {
        XEvent inEvent;
        Props props{true};
        // handle window events first because window Events are also XEvents
        while(XCheckWindowEvent(m_display, m_window, WindowUnixImpl::EVENT_MASK, &inEvent))
        {
            switch(inEvent.type)
            {
            case KeyPress:
                {
                    props["keycode"] = (unsigned int)inEvent.xkey.keycode;
                    props["repeat"] = m_repeatKey;
                    ATMAContext::getContext().dispatchWindowEvent(WindowEvent{
                        shared_from_this(), WindowEventEnum::KeyDowned, props});
                    break;
                }
            case KeyRelease:
                {
                    if(XEventsQueued(m_display, QueuedAlready))
                    {
                        XEvent next;
                        XPeekEvent(m_display, &next);
                        if(next.type == KeyPress && next.xkey.time
                           && inEvent.xkey.keycode == next.xkey.keycode)
                        {
                            m_repeatKey = true;
                        }
                        else
                        {
                            m_repeatKey = false;
                        }
                    }
                    else
                    {
                        m_repeatKey = false;
                    }
                    props["keycode"] = (unsigned int)inEvent.xkey.keycode;
                    props["repeat"] = m_repeatKey;
                    ATMAContext::getContext().dispatchWindowEvent(WindowEvent{
                        shared_from_this(), WindowEventEnum::KeyUpped, props});
                    break;
                }
            case ConfigureNotify:
                {
                    XConfigureEvent xConfEvent = inEvent.xconfigure;
                    if(m_size.x != xConfEvent.width || m_size.y != xConfEvent.height)
                    {
                        props["width"] = (unsigned int)xConfEvent.width;
                        props["height"] = (unsigned int)xConfEvent.height;
                        ATMAContext::getContext().dispatchWindowEvent(WindowEvent{
                            shared_from_this(), WindowEventEnum::Resized, std::move(props)});
                    }
                }
                break;
            case Expose:
                redraw();
                break;
            }
        }
        // X Server events
        while(XPending(m_display))
        {
            XNextEvent(m_display, &inEvent);
            switch(inEvent.type)
            {
            case ClientMessage:
                if(inEvent.xclient.data.l[0] == m_deleteMessage) // window close
                {
                    ATMAContext::getContext().dispatchWindowEvent(WindowEvent{
                        shared_from_this(), WindowEventEnum::Closed, std::move(props)});
                }
            }
        }
    }

    void WindowUnixImpl::swapBuffers()
    {
        glXSwapBuffers(m_display, m_window);
    }

    Display *WindowUnixImpl::getDisplay()
    {
        static Display *display;
        if(display == nullptr)
        {
            display = XOpenDisplay(NULL);
        }
        return display;
    }

    GLXFBConfig WindowUnixImpl::getFrameBufferConfig(Display *l_display)
    {
        static GLXFBConfig *bestFbc;
        if(bestFbc == nullptr)
        {
            bestFbc = new GLXFBConfig{};
            int fbcount;

            GLXFBConfig *fbc = glXChooseFBConfig(
                l_display, DefaultScreen(l_display), ATConst::DEFAULT_VISUAL_ATTRIBUTES, &fbcount
            );
            if(!fbc)
            {
                ATMA_ENGINE_WARN("Failed to retrieve a framebuffer config\n");
                exit(1);
            }
            ATMA_ENGINE_TRACE("Found {} matching FB configs", fbcount);

            // Pick the FB config/visual with the most samples per pixel
            int best_fbc = -1, worst_fbc = -1, best_num_samp = -1, worst_num_samp = 999;

            int i;
            for(i = 0; i < fbcount; ++i)
            {
                XVisualInfo *vi = glXGetVisualFromFBConfig(l_display, fbc[i]);
                if(vi)
                {
                    int samp_buf, samples;
                    glXGetFBConfigAttrib(l_display, fbc[i], GLX_SAMPLE_BUFFERS, &samp_buf);
                    glXGetFBConfigAttrib(l_display, fbc[i], GLX_SAMPLES, &samples);

                    if(best_fbc < 0 || samp_buf && samples > best_num_samp)
                        best_fbc = i, best_num_samp = samples;
                    if(worst_fbc < 0 || !samp_buf || samples < worst_num_samp)
                        worst_fbc = i, worst_num_samp = samples;
                }
                XFree(vi);
            }

            *bestFbc = fbc[best_fbc];

            XFree(fbc);
        }
        return *bestFbc;
    }

    void WindowUnixImpl::redraw()
    {
        XFillRectangle(
            m_display, m_window, DefaultGC(m_display, m_screen), 0, 0, m_size.x, m_size.y
        );
    }

}
#else
#    error Linux implementation included in non-Linux target
#endif