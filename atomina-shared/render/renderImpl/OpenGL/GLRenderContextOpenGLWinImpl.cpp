#ifdef _WINDOWS
#    include "pch.hpp"
#    include "GLRenderContextOpenGLWinImpl.hpp"

namespace ATMA
{
    GLRenderContextOpenGLWinImpl::GLRenderContextOpenGLWinImpl(): GLRenderContext()
    {
        GLenum err;
        HGLRC tempContext;
        int pixelFormat;
        ATMA_ENGINE_INFO("Constructing Windows OpenGL Render Context");
        // pass windows window handler to get window device context
        m_hdc = GetDC(NULL);
        pixelFormat = ChoosePixelFormat(m_hdc, &ATConst::DEFAULT_PIXEL_FORMAT_D);
        SetPixelFormat(m_hdc, pixelFormat, &ATConst::DEFAULT_PIXEL_FORMAT_D);
        tempContext = wglCreateContext(m_hdc);
        wglMakeCurrent(m_hdc, tempContext);
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

        err = wglewInit();
        if(GLEW_OK != err)
        {
            /* Problem: glewInit failed, something is seriously wrong. */
            std::string errString =
                std::string(reinterpret_cast<const char *>(glewGetErrorString(err)));
            ATMA_ENGINE_ERROR("Error: {}", errString);
        }
        else
        {
            ATMA_ENGINE_INFO("WGLEW INIT OK!");
        }
        // Now create a proper context

        int attribs[] = {
            WGL_CONTEXT_MAJOR_VERSION_ARB,
            3,
            WGL_CONTEXT_MINOR_VERSION_ARB,
            1,
            WGL_CONTEXT_FLAGS_ARB,
            0,
            0};

        if(wglewIsSupported("WGL_ARB_create_context") == 1)
        {
            m_hglrc = wglCreateContextAttribsARB(m_hdc, 0, attribs);
            wglMakeCurrent(m_hdc, m_hglrc);
        }
    }

    GLRenderContextOpenGLWinImpl::~GLRenderContextOpenGLWinImpl()
    {
        ATMA_ENGINE_INFO("Destroying Window OpenGL Render Context");
        // make the rendering context not current
        wglMakeCurrent(NULL, NULL);

        // delete the rendering context
        wglDeleteContext(m_hglrc);
    }

    void GLRenderContextOpenGLWinImpl::setWindow(std::shared_ptr<AppWindow> l_window)
    {
        ATMA_ENGINE_INFO("Setting Render Context to Windows Window {0}", l_window->getName());
        // get Device context from window handler
        // type case Window into WindowWinImpl
        // using static cast since the only subclass for windows is windowswinimpl
        std::shared_ptr<WindowWinImpl> winWindow =
            std::static_pointer_cast<WindowWinImpl>(l_window);
        m_hdc = GetDC(winWindow->m_windowHandle);
        // create new context
        int pixelFormat = ChoosePixelFormat(m_hdc, &ATConst::DEFAULT_PIXEL_FORMAT_D);
        SetPixelFormat(m_hdc, pixelFormat, &ATConst::DEFAULT_PIXEL_FORMAT_D);
        int attribs[] = {
            WGL_CONTEXT_MAJOR_VERSION_ARB,
            3,
            WGL_CONTEXT_MINOR_VERSION_ARB,
            1,
            WGL_CONTEXT_FLAGS_ARB,
            0,
            0};

        // swap contexts
        if(wglewIsSupported("WGL_ARB_create_context") == 1)
        {
            auto newContext = wglCreateContextAttribsARB(m_hdc, 0, attribs);
            wglMakeCurrent(NULL, NULL);
            wglDeleteContext(m_hglrc);
            wglMakeCurrent(m_hdc, newContext);
            m_hglrc = newContext;
        }
    }

    void GLRenderContextOpenGLWinImpl::draw(std::shared_ptr<Renderable> l_renderable)
    {
        auto vertArray = ATMA::VertexArray::makeBuffer({
            {3, 8, 0},
            {3, 8, 3},
            {2, 8, 6}
        });

        auto vertBuf =
            ATMA::VertexBuffer::makeBuffer({1.0f,  1.0f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
                                            1.0f,  -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
                                            -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
                                            -1.0f, 1.0f,  0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f});

        auto indexBuf = ATMA::IndexBuffer::makeBuffer({0, 1, 2, 0, 2, 3});

        std::shared_ptr<ATMA::GLProgram> shaderprog = ATMA::GLProgram::makeDefaultProgram();

        vertArray->bind();

        indexBuf->bind();

        vertBuf->bind();

        vertArray->bindLayout();
        shaderprog->exec();
        auto transform =
            ATMA::translationMatrix<float>(l_renderable->m_screenPos.x, l_renderable->m_screenPos.y)
            * ATMA::scalingMatrix<float>(l_renderable->m_region.x, l_renderable->m_region.y);
        //    * rotationMatrix(l_rot);
        shaderprog->setUniformMat3f("u_transform", transform);
        l_renderable->m_texture->bind();
        shaderprog->exec();

        // bind textures on corresponding texture units
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

}

#else
#    error Windows implementation included in non-Windows target
#endif