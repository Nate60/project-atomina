#include "pch.hpp"
#include "GLRenderContextDummyImpl.hpp"

namespace ATMA
{

    GLRenderContextDummyImpl::GLRenderContextDummyImpl(): GLRenderContext()
    {
        ATMA_ENGINE_INFO("Constructing Dummy Render Context");
    }

    GLRenderContextDummyImpl::~GLRenderContextDummyImpl()
    {
        ATMA_ENGINE_INFO("Destroying Dummy Render Context");
    }

    void GLRenderContextDummyImpl::setWindow(std::shared_ptr<AppWindow> l_window) {}

}
