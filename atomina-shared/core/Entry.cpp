#include "pch.hpp"
#include "Entry.hpp"

#define ATMA_OPENGL
/*
 * DLL entry point into execution
 */
namespace ATMA
{
#ifdef _WINDOWS

    void startGame(std::unique_ptr<Game> l_game)
    {
        // required for winsock
        WSADATA wsaData;
        WSAStartup(MAKEWORD(2, 2), &wsaData);

        Log::Init();
        ATMA_ENGINE_INFO("Init logger!");

#    ifdef ATMA_OPENGL

        HDC winDeviceContext = GetDC(NULL);
        int pixelFormat = ChoosePixelFormat(winDeviceContext, &ATConst::DEFAULT_PIXEL_FORMAT_D);

        SetPixelFormat(winDeviceContext, pixelFormat, &ATConst::DEFAULT_PIXEL_FORMAT_D);
        HGLRC tempContext = wglCreateContext(winDeviceContext);
        wglMakeCurrent(winDeviceContext, tempContext);

        GLenum err = glewInit();
        if(GLEW_OK != err)
        {
            ATMA_ENGINE_ERROR("GLEW is not initialized!");
        }
        else
        {
            ATMA_ENGINE_INFO("Atomina Engine has initialized OpenGL!");
            wglMakeCurrent(NULL, NULL);
            wglDeleteContext(tempContext);
        }
#    endif

        try
        {
            l_game->run();
        }
        catch(AtominaException e)
        {
            ATMA_ENGINE_ERROR("Fatal error {0} shutting down...", e.what());
        }
        catch(std::exception e)
        {
            ATMA_ENGINE_ERROR("Fatal error {0} shutting down...", e.what());
        }
    }
}
#elif linux
#    define GLX_CONTEXT_MAJOR_VERSION_ARB 0x2091
#    define GLX_CONTEXT_MINOR_VERSION_ARB 0x2092

    static bool isExtensionSupported(const char *extList, const char *extension)
    {
        const char *start;
        const char *where, *terminator;

        /* Extension names should not have spaces. */
        where = strchr(extension, ' ');
        if(where || *extension == '\0')
            return false;

        /* It takes a bit of care to be fool-proof about parsing the
           OpenGL extensions string. Don't be fooled by sub-strings,
           etc. */
        for(start = extList;;)
        {
            where = strstr(start, extension);

            if(!where)
                break;

            terminator = where + strlen(extension);

            if(where == start || *(where - 1) == ' ')
                if(*terminator == ' ' || *terminator == '\0')
                    return true;

            start = terminator;
        }

        return false;
    }

    static bool ctxErrorOccurred = false;

    static int ctxErrorHandler(Display *dpy, XErrorEvent *ev)
    {
        ctxErrorOccurred = true;
        return 0;
    }

    GLXContext createGLXContext(Display *l_display)
    {
        // check if the display given is valid
        if(!l_display)
        {
            ATMA_ENGINE_ERROR("Failed to open X display");
            return nullptr;
        }

        auto screenid = DefaultScreen(l_display);

        if(!screenid)
        {
            ATMA_ENGINE_ERROR("Failed to make default screen");
            return nullptr;
        }

        // get glx version
        ATMA_ENGINE_TRACE("Getting GLX version");
        int glx_major, glx_minor;

        // FBConfigs were added in GLX version 1.3.
        if(!glXQueryVersion(l_display, &glx_major, &glx_minor)
           || ((glx_major == 1) && (glx_minor < 3)) || (glx_major < 1))
        {
            ATMA_ENGINE_ERROR("Invalid GLX version");
            return nullptr;
        }

        ATMA_ENGINE_TRACE("GLX Version {0}.{1}", glx_major, glx_minor);

        ATMA_ENGINE_TRACE("Getting frame buffer configs");
        int fbcount;
        GLXFBConfig *fbc =
            glXChooseFBConfig(l_display, screenid, ATConst::DEFAULT_VISUAL_ATTRIBUTES, &fbcount);

        if(!fbc)
        {
            ATMA_ENGINE_ERROR("Failed to retrieve a framebuffer config\n");
            return nullptr;
        }

        ATMA_ENGINE_TRACE("Getting XVisualInfos");
        int best_fbc = -1, worst_fbc = -1, best_num_samp = -1, worst_num_samp = 999;

        for(int i = 0; i < fbcount; ++i)
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

        GLXFBConfig bestFbc = fbc[best_fbc];

        XFree(fbc);

        XVisualInfo *vi = glXGetVisualFromFBConfig(l_display, bestFbc);

        ATMA_ENGINE_TRACE("Creating Colour map");
        XSetWindowAttributes swa;
        Colormap cmap;
        swa.colormap = cmap =
            XCreateColormap(l_display, RootWindow(l_display, vi->screen), vi->visual, AllocNone);
        swa.background_pixmap = 0L;
        swa.border_pixel = 0;
        swa.event_mask = StructureNotifyMask;

        ATMA_ENGINE_TRACE("Creating window");
        Window win = XCreateWindow(
            l_display,
            RootWindow(l_display, vi->screen),
            0,
            0,
            100,
            100,
            0,
            vi->depth,
            InputOutput,
            vi->visual,
            CWBorderPixel | CWColormap | CWEventMask,
            &swa
        );

        if(!win)
        {
            ATMA_ENGINE_ERROR("Failed to create window");
            return nullptr;
        }

        XFree(vi);
        XStoreName(l_display, win, "GL 3.0 Window");
        XMapWindow(l_display, win);

        GLXContext ctx = 0;

        ctxErrorOccurred = false;
        int (*oldHandler)(Display *, XErrorEvent *) = XSetErrorHandler(&ctxErrorHandler);

        const char *glxExts = glXQueryExtensionsString(l_display, DefaultScreen(l_display));

        if(!isExtensionSupported(glxExts, "GLX_ARB_create_context"))
        {
            ATMA_ENGINE_TRACE("Old GLX Context Creation");
            ctx = glXCreateNewContext(l_display, bestFbc, GLX_RGBA_TYPE, 0, True);
        }
        else
        {
            ATMA_ENGINE_TRACE("New GLX Context Creation");
            int context_attribs[] = {
                GLX_CONTEXT_MAJOR_VERSION_ARB,
                3,
                GLX_CONTEXT_MINOR_VERSION_ARB,
                0,
                // GLX_CONTEXT_FLAGS_ARB        , GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
                0L};
            ctx = glXCreateContextAttribsARB(l_display, bestFbc, 0, True, context_attribs);
            XSync(l_display, False);
        }

        XSetErrorHandler(oldHandler);

        glXMakeCurrent(l_display, win, ctx);
        if(!ctx || ctxErrorOccurred)
        {
            ATMA_ENGINE_ERROR("Failed to create GLX context");
        }
        return ctx;
    }
}

int main()
{
    ATMA::Log::Init();
    ATMA_ENGINE_INFO("Init logger!");

#    ifdef ATMA_OPENGL

    ATMA_ENGINE_TRACE("Opening X display");

    Display *display = XOpenDisplay(NULL);
    GLXContext ctx = ATMA::createGLXContext(display);

    if(GLEW_OK != glewInit())
    {
        ATMA_ENGINE_ERROR("GLEW is not initialized!");
    }
    else
    {
        ATMA_ENGINE_INFO("Atoma Engine has initialized OpenGL!");

        glXMakeCurrent(display, 0, 0);
        glXDestroyContext(display, ctx);
    }
#    endif

    std::unique_ptr<ATMA::Game> app = ATMA::CreateGame();
    try
    {
        app->run();
    }
    catch(ATMA::AtominaException e)
    {
        ATMA_ENGINE_ERROR("Fatal error {0} shutting down...", e.what());
    }
    catch(std::exception e)
    {
        ATMA_ENGINE_ERROR("Fatal error {0} shutting down...", e.what());
    }
}
#endif