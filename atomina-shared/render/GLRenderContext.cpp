#include "pch.hpp"
#include "GLRenderContext.hpp"
#ifdef ATMA_OPENGL
#    include "renderImpl/OpenGL/GLRenderContextOpenGLImpl.hpp"
#    define __ATMAMAKEGLRENDERCONTEXT() std::make_shared<GLRenderContextOpenGLImpl>()
#else
#    include "renderImpl/Dummy/GLRenderContextDummyImpl.hpp"
#    define __ATMAMAKEGLRENDERCONTEXT() std::make_shared<GLRenderContextDummyImpl>()
#endif

namespace ATMA
{

    GLRenderContext::GLRenderContext() {}

    GLRenderContext::~GLRenderContext() {}

    std::shared_ptr<GLRenderContext> GLRenderContext::getRenderContext()
    {
        static std::once_flag flag{};
        static std::shared_ptr<GLRenderContext> renderCtx;
        std::call_once(flag, [&]() { renderCtx = __ATMAMAKEGLRENDERCONTEXT(); });
        return renderCtx;
    }

}