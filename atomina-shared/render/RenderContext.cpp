#include "pch.hpp"
#include "RenderContext.hpp"
#include "GLAD/RenderContextGLADImpl.hpp"

namespace ATMA
{

    std::unique_ptr<RenderContext> RenderContext::makeRenderContext()
    {
#ifdef ATMA_USE_OPENGL
        return std::move(std::make_unique<RenderContextGLADImpl>());
#endif
    }

    RenderContext::RenderContext() {}

    RenderContext::~RenderContext() {}

}