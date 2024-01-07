#include "pch.hpp"
#include "GLRenderer.hpp"

namespace ATMA
{
    GLRenderer::GLRenderer()
    {
        m_Ctx = GLRenderContext::makeRenderContext();
    }

    GLRenderer::~GLRenderer() {}

    void GLRenderer::draw(std::shared_ptr<Renderable> l_drawable) {}

    void GLRenderer::setWindow(std::shared_ptr<AppWindow> l_window)
    {
        m_Ctx->setWindow(l_window);
    }

}