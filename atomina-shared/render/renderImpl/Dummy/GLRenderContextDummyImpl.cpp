#include "pch.hpp"
#include "GLRenderContextDummyImpl.hpp"

namespace ATMA
{

    // default constructor
    GLRenderContextDummyImpl::GLRenderContextDummyImpl() {}

    // default deconstructor
    GLRenderContextDummyImpl::~GLRenderContextDummyImpl() {}

    void GLRenderContextDummyImpl::init() {}

    void GLRenderContextDummyImpl::setViewPort(const Vec2<int> &l_pos, const Vec2<int> &l_size) {}

    void GLRenderContextDummyImpl::clear() {}

    void GLRenderContextDummyImpl::toggleBlend(const bool &l_toggle) {}

}