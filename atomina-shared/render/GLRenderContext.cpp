#include "pch.hpp"
#include "GLRenderContext.hpp"
#ifdef ATMA_OPENGL
#    ifdef __linux__
#        include "renderImpl/OpenGL/GLRenderContextOpenGLUnixImpl.hpp"
#        define __ATMAMAKEGLRENDERCTX()                                                            \
            return std::move(std::make_unique<GLRenderContextOpenGLUnixImpl>())
#    elif _WINDOWS
#        include "renderImpl/OpenGL/GLRenderContextOpenGLWinImpl.hpp"
#        define __ATMAMAKEGLRENDERCTX()                                                            \
            return std::move(std::make_unique<GLRenderContextOpenGLWinImpl>())
#    endif
#else
#    include "renderImpl/Dummy/GLRenderContextDummyImpl.hpp"
#    define __ATMAMAKEGLRENDERCTX() return std::move(std::make_unique<GLRenderContextDummyImpl>())
#endif

namespace ATMA
{

    GLRenderContext::GLRenderContext() {}

    GLRenderContext::~GLRenderContext() {}

    void GLRenderContext::setFont(const std::shared_ptr<Font> l_font)
    {
        m_font = l_font;
    }

    void GLRenderContext::add(std::shared_ptr<GLRenderable> l_element)
    {
        m_elementStack.push(l_element);
    }

    std::unique_ptr<GLRenderContext> GLRenderContext::makeRenderContext()
    {
        __ATMAMAKEGLRENDERCTX();
    }

}