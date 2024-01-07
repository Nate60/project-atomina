#ifdef __linux__
#    include "pch.hpp"
#    include "GLRenderContextOpenGLUnixImpl.hpp"
#    define GLX_CONTEXT_MAJOR_VERSION_ARB 0x2091
#    define GLX_CONTEXT_MINOR_VERSION_ARB 0x2092
typedef GLXContext (*glXCreateContextAttribsARBProc
)(Display *, GLXFBConfig, GLXContext, bool, const int *);

namespace ATMA
{

    // Get a matching FB config
    const static int GLX_ATTRIBUTES[] = {
        GLX_X_RENDERABLE,
        GL_TRUE,
        GLX_DRAWABLE_TYPE,
        GLX_WINDOW_BIT,
        GLX_RENDER_TYPE,
        GLX_RGBA_BIT,
        GLX_X_VISUAL_TYPE,
        GLX_TRUE_COLOR,
        GLX_RED_SIZE,
        8,
        GLX_GREEN_SIZE,
        8,
        GLX_BLUE_SIZE,
        8,
        GLX_ALPHA_SIZE,
        8,
        GLX_DEPTH_SIZE,
        24,
        GLX_STENCIL_SIZE,
        8,
        GLX_DOUBLEBUFFER,
        GL_TRUE,
        // GLX_SAMPLE_BUFFERS  , 1,
        // GLX_SAMPLES         , 4,
        0L};

    // Helper to check for extension string presence.  Adapted from:
    //   http://www.opengl.org/resources/features/OGLextensions/
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

    GLRenderContextOpenGLUnixImpl::GLRenderContextOpenGLUnixImpl(): GLRenderContext()
    {
        int glx_major, glx_minor, screenId, fbcount;
        Window root;
        GLXFBConfig bestFbc;
        GLXFBConfig *fbc;
        const char *glxExts;
        GLenum err;
        ATMA_ENGINE_INFO("Constructing Unix OpenGL Render Context");
        // Set X Server Error handler
        XSetErrorHandler(
            [](Display *dsp, XErrorEvent *error)
            {
                char errorstring[128];
                XGetErrorText(dsp, error->error_code, errorstring, 128);
                ATMA_ENGINE_ERROR("X Server encountered error {0}", std::string(errorstring));
                return 0;
            }
        );

        // first creat temporary OpenGL Context to init GLEW and GLXEW
        m_display = XOpenDisplay(NULL);
        if(m_display == NULL)
        {
            ATMA_ENGINE_ERROR("Failed to open display");
        }
        if(!glXQueryVersion(m_display, &glx_major, &glx_minor))
        {
            ATMA_ENGINE_ERROR("Invalid GLX Version");
        }
        ATMA_ENGINE_INFO("Using GLX Version {0:d}.{1:d}", glx_major, glx_minor);
        root = DefaultRootWindow(m_display);
        screenId = DefaultScreen(m_display);

        m_visualInfo = glXChooseVisual(m_display, 0, m_attributes);
        m_glContext = glXCreateContext(m_display, m_visualInfo, NULL, GL_TRUE);
        glXMakeCurrent(m_display, root, m_glContext);
        ATMA_ENGINE_INFO("Created Open GL temp context");
        err = glewInit();
        if(GLEW_OK != err)
        {
            /* Problem: glewInit failed, something is seriously wrong. */
            std::string errString =
                std::string(reinterpret_cast<const char *>(glewGetErrorString(err)));
            ATMA_ENGINE_ERROR("Error: {}", errString);
        }
        else
        {
            ATMA_ENGINE_INFO("GLEW INIT OK!");
        }

        err = glxewInit();
        if(GLEW_OK != err)
        {
            /* Problem: glewInit failed, something is seriously wrong. */
            std::string errString =
                std::string(reinterpret_cast<const char *>(glewGetErrorString(err)));
            ATMA_ENGINE_ERROR("Error: {}", errString);
        }
        else
        {
            ATMA_ENGINE_INFO("GLXEW INIT OK!");
        }
        // Now create a proper context

        fbc = glXChooseFBConfig(m_display, screenId, GLX_ATTRIBUTES, &fbcount);
        if(fbc == 0)
        {
            ATMA_ENGINE_ERROR("Failed to retrieve framebuffer");
            XCloseDisplay(m_display);
        }
        ATMA_ENGINE_INFO("Got FrameBuffer Config");
        // Pick the FB config/visual with the most samples per pixel
        int best_fbc = -1, worst_fbc = -1, best_num_samp = -1, worst_num_samp = 999;
        for(int i = 0; i < fbcount; ++i)
        {
            XVisualInfo *vi = glXGetVisualFromFBConfig(m_display, fbc[i]);
            if(vi != 0)
            {
                int samp_buf, samples;
                glXGetFBConfigAttrib(m_display, fbc[i], GLX_SAMPLE_BUFFERS, &samp_buf);
                glXGetFBConfigAttrib(m_display, fbc[i], GLX_SAMPLES, &samples);

                if(best_fbc < 0 || (samp_buf && samples > best_num_samp))
                {
                    best_fbc = i;
                    best_num_samp = samples;
                }
                if(worst_fbc < 0 || !samp_buf || samples < worst_num_samp)
                    worst_fbc = i;
                worst_num_samp = samples;
            }
            XFree(vi);
        }
        bestFbc = fbc[best_fbc];
        XFree(fbc); // Make sure to free this!

        m_visualInfo = glXGetVisualFromFBConfig(m_display, bestFbc);

        // Get the default screen's GLX extension list
        glxExts = glXQueryExtensionsString(m_display, screenId);

        // Check for the GLX_ARB_create_context extension string and the function.
        // If either is not present, use GLX 1.3 context creation method.
        if(!isExtensionSupported(glxExts, "GLX_ARB_create_context") || !glXCreateContextAttribsARB)
        {
            ATMA_ENGINE_WARN(
                "glXCreateContextAttribsARB() not found ... using old-style GLX context"
            );
            glXMakeCurrent(m_display, 0L, NULL);
            glXDestroyContext(m_display, m_glContext);
            m_glContext = glXCreateNewContext(m_display, bestFbc, GLX_RGBA_TYPE, 0, GL_TRUE);
            ATMA_ENGINE_INFO("Created OpenGL Context Version: {0}", glGetString(GL_VERSION));
        }
        else
        {
            ATMA_ENGINE_INFO("Creating OpenGL Context 3.0+");
            int context_attribs[] = {
                GLX_CONTEXT_MAJOR_VERSION_ARB,
                3,
                GLX_CONTEXT_MINOR_VERSION_ARB,
                0,
                // GLX_CONTEXT_FLAGS_ARB        , GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
                0L};

            glXMakeCurrent(m_display, 0L, NULL);
            glXDestroyContext(m_display, m_glContext);
            m_glContext =
                glXCreateContextAttribsARB(m_display, bestFbc, 0, GL_TRUE, context_attribs);
        }
        glXMakeCurrent(m_display, root, m_glContext);
    }

    GLRenderContextOpenGLUnixImpl::~GLRenderContextOpenGLUnixImpl()
    {
        ATMA_ENGINE_INFO("Destroying Unix OpenGL Render Context");
        glXMakeCurrent(m_display, 0L, NULL);
        glXDestroyContext(m_display, m_glContext);
    }

    void GLRenderContextOpenGLUnixImpl::setWindow(std::shared_ptr<AppWindow> l_window)
    {
        ATMA_ENGINE_INFO("Setting Render Context to Unix Window {0}", l_window->getName());
        // get Device context from window handler
        // type case Window into WindowUnixImpl
        // using static cast since the only subclass for unix is windowsUnixImpl
        std::shared_ptr<WindowUnixImpl> unixWindow =
            std::static_pointer_cast<WindowUnixImpl>(l_window);
        Window win = unixWindow->m_window;
        m_display = unixWindow->m_display;
        GLXContext localCtx = glXGetCurrentContext();
        if(localCtx == NULL)
        {
            ATMA_ENGINE_ERROR("No Current Context");
        }
        else if(localCtx != m_glContext)
        {
            ATMA_ENGINE_WARN("local context differs from current context");
        }
        glXMakeCurrent(m_display, win, localCtx);
    }
}
#else
#    error Linux implementation included in non-Linux target
#endif