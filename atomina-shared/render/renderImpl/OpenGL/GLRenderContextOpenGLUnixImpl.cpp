#ifdef __linux__
#    include "pch.hpp"
#    include "GLRenderContextOpenGLUnixImpl.hpp"
typedef GLXContext (*glXCreateContextAttribsARBProc
)(Display *, GLXFBConfig, GLXContext, bool, const int *);

namespace ATMA
{

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
        int glx_major, glx_minor, screenId;
        Window root;
        GLXFBConfig bestFbc;
        const char *glxExts;
        GLenum err;
        ATMA_ENGINE_INFO("Constructing Unix OpenGL Render Context");
        // Set X Server Error handler
        XSetErrorHandler(
            [](Display *dsp, XErrorEvent *error)
            {
                char errorstring[128];
                XGetErrorText(dsp, error->error_code, errorstring, 128);
                ATMA_ENGINE_ERROR(
                    "X Server encountered error Type:{0} | {1}",
                    error->error_code,
                    std::string(errorstring)
                );
                return 0;
            }
        );

        // first creat temporary OpenGL Context to init GLEW and GLXEW
        m_display = WindowUnixImpl::getDisplay();
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

        bestFbc = WindowUnixImpl::getFrameBufferConfig(m_display);

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
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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
        ATMA_ENGINE_INFO(
            "Window size x:{0},y:{1}", unixWindow->getSize().x, unixWindow->getSize().y
        );
        glViewport(0, 0, unixWindow->getSize().x, unixWindow->getSize().y);
        glXMakeCurrent(m_display, win, localCtx);
    }

    void GLRenderContextOpenGLUnixImpl::setSize(const Vec2<unsigned int> &l_size)
    {
        glViewport(0, 0, l_size.x, l_size.y);
    }

    void GLRenderContextOpenGLUnixImpl::draw()
    {
        std::shared_ptr<ATMA::GLProgram> shaderprog = GLProgram::makeDefaultProgram();

        shaderprog->exec();
        while(!m_elementStack.empty())
        {
            auto &element = m_elementStack.top();
            if(std::holds_alternative<std::shared_ptr<GLTexture>>(element->m_element))
            {
                auto transform =
                    translationMatrix<float>(
                        element->m_screenPos.x, element->m_screenPos.y
                    )
                    * scalingMatrix<float>(element->m_region.x, element->m_region.y)
                   * rotationMatrix(element->m_rot);
                auto sourcetransform = translationMatrix<float>(element->m_srcPos.x, element->m_srcPos.y)
                    * scalingMatrix<float>(element->m_srcRegion.x, element->m_srcRegion.y);
                shaderprog->setUniformMat3f("u_transform", transform);
                shaderprog->setUniformMat3f("u_source", sourcetransform);
                std::get<std::shared_ptr<GLTexture>>(element->m_element)->bind();
                shaderprog->exec();

                // bind textures on corresponding texture units
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            }
            else
            {
                float advance = 0;
                m_font->m_fontTexture->bind();
                auto text = std::get<std::string>(element->m_element);
                for(auto &c: text)
                {
                    auto transform =
                        translationMatrix(element->m_screenPos.x + advance, element->m_screenPos.y)
                        * scalingMatrix(element->m_region.x, element->m_region.y);
                    shaderprog->setUniformMat3f("u_transform", transform);
                    auto srcTransform =
                        translationMatrix(
                            (c % 11) * Font::GLYPH_SIZE_RATIO_X, (c / 11) * Font::GLYPH_SIZE_RATIO_Y
                        )
                        * scalingMatrix(Font::GLYPH_SIZE_RATIO_X, Font::GLYPH_SIZE_RATIO_Y);
                    shaderprog->setUniformMat3f("u_source", srcTransform);
                    shaderprog->exec();
                    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
                    advance += element->m_region.x * 2; // I dont' understand why times 2
                }
            }
            m_elementStack.pop();
        }
    }

    void GLRenderContextOpenGLUnixImpl::clear()
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    }
#else
#    error Linux implementation included in non-Linux target
#endif