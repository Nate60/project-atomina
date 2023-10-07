#ifdef _WINDOWS
#include "pch.hpp"
#include "GLRenderContextOpenGLWinImpl.hpp"

namespace ATMA
{
    GLRenderContextOpenGLWinImpl::GLRenderContextOpenGLWinImpl() : GLRenderContext()
    {
        ATMA_ENGINE_INFO("Constructing Windows OpenGL Render Context");
        // pass windows window handler to get window device context
        m_hdc = GetDC(NULL);
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
}

#else
#    error Windows implementation included in non-Windows target
#endif