#ifdef __linux__
#    include "pch.hpp"
#    include "WindowUnixImpl.hpp"
#    include "util/ATConst.hpp"

namespace ATMA
{

    WindowUnixImpl::WindowUnixImpl(const Vec2<int> &l_size, const std::string &l_name):
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
        XFreeColormap(m_display, m_colourMap);
    }

    void WindowUnixImpl::setSize(Vec2<int> l_size) {}

    Vec2<int> WindowUnixImpl::getSize()
    {
        return m_size;
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
            printf("Getting matching framebuffer configs\n");

            GLXFBConfig *fbc = glXChooseFBConfig(
                l_display, DefaultScreen(l_display), ATConst::DEFAULT_VISUAL_ATTRIBUTES, &fbcount
            );
            if(!fbc)
            {
                printf("Failed to retrieve a framebuffer config\n");
                exit(1);
            }
            printf("Found %d matching FB configs.\n", fbcount);

            // Pick the FB config/visual with the most samples per pixel
            printf("Getting XVisualInfos\n");
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

                    printf(
                        "  Matching fbconfig %d, visual ID 0x%2x: SAMPLE_BUFFERS = %d,"
                        " SAMPLES = %d\n",
                        i,
                        vi->visualid,
                        samp_buf,
                        samples
                    );

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

}
#else
#    error Linux implementation included in non-Linux target
#endif