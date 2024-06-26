#ifdef _WINDOWS
#    include "pch.hpp"
#    include "GLRenderContextOpenGLWinImpl.hpp"

namespace ATMA
{
    typedef const char *(WINAPI *wglGetExtensionsStringARB_t)(HDC theDeviceContext);

    GLRenderContextOpenGLWinImpl::GLRenderContextOpenGLWinImpl(): GLRenderContext()
    {
        //Some systems require that a window is created first
        //So we will create a ghost window to load the extensions into memory
        WindowWinImpl win{};
        ShowWindow(win.m_windowHandle, SW_HIDE);
        GLenum err;
        HGLRC tempContext;
        int pixelFormat = -1;
        ATMA_ENGINE_INFO("Constructing Windows OpenGL Render Context");
        // pass windows window handler to get window device context
        m_hdc = GetDC(win.m_windowHandle);
        PIXELFORMATDESCRIPTOR aFormat = ATConst::DEFAULT_PIXEL_FORMAT_D;
        pixelFormat = ChoosePixelFormat(m_hdc, &aFormat);
        if(pixelFormat == 0)
        {
            ATMA_ENGINE_WARN("Failed to choose pixel format");
        }
        DescribePixelFormat(m_hdc, pixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &aFormat);
        if(!SetPixelFormat(m_hdc, pixelFormat, &aFormat))
        {
            ATMA_ENGINE_WARN("Failed to failed pixel format");
        }
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
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void GLRenderContextOpenGLWinImpl::setSize(const Vec2<unsigned int> &l_size)
    {
        glViewport(0, 0, l_size.x, l_size.y);
    }

    void GLRenderContextOpenGLWinImpl::clear()
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void GLRenderContextOpenGLWinImpl::draw()
    {
        std::shared_ptr<ATMA::GLProgram> shaderprog = GLProgram::makeDefaultProgram();

        shaderprog->exec();
        while(!m_elementStack.empty())
        {
            auto &element = m_elementStack.top();
            if(std::holds_alternative<std::shared_ptr<GLTexture>>(element->m_element))
            {
                auto transform =
                    translationMatrix<float>(element->m_screenPos.x, element->m_screenPos.y)
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

}

#else
#    error Windows implementation included in non-Windows target
#endif