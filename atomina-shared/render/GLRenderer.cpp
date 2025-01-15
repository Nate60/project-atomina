#include "pch.hpp"
#include "GLRenderer.hpp"

namespace ATMA
{

    GLRenderer::GLRenderer()
    {
        m_renderCtx = GLRenderContext::getRenderContext();
    }

    GLRenderer::~GLRenderer() {}

    void GLRenderer::toggleBlend(const bool &l_toggle)
    {
        m_renderCtx->toggleBlend(l_toggle);
    }

    void GLRenderer::setFrameBufferDimensions(const int &w, const int &h)
    {
        m_renderCtx->setViewPort({0, 0}, {w, h});
    }

    void GLRenderer::setWindow(std::shared_ptr<AppWindow> l_win)
    {
        static std::once_flag once;
        glfwMakeContextCurrent(l_win->m_windowHandle);
        std::call_once(once, [&]() { m_renderCtx->init(); });
    }

    void GLRenderer::startScene(const GLCamera &l_camera)
    {
        m_camera = l_camera;
    }

    void GLRenderer::addElement(std::shared_ptr<GLRenderable> l_renderable)
    {
        m_elementStack.push(l_renderable);
    }

    void GLRenderer::finishScene()
    {
        Props p{};
        p["u_camera"] = m_camera.getProjectionMatrix();
        m_renderCtx->clear();
        while(!m_elementStack.empty())
        {
            auto &element = m_elementStack.top();
            element->draw(p);
            m_elementStack.pop();
        }
    }

}