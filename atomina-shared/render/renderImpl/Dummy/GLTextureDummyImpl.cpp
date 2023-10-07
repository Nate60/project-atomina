#include "pch.hpp"
#include "GLTextureDummyImpl.hpp"
#include "util/Log.hpp"

namespace ATMA
{
    // constructor with name and filename of resource
    GLTextureDummyImpl::GLTextureDummyImpl(const std::string &l_fileName): GLTexture(l_fileName)
    {
        m_bindID = 0;
    }

    GLTextureDummyImpl::GLTextureDummyImpl(): GLTexture()
    {
        m_bindID = 0;
    }

    GLTextureDummyImpl::~GLTextureDummyImpl() {}

    void GLTextureDummyImpl::bind() {}

    void GLTextureDummyImpl::unbind() {}

    std::shared_ptr<GLTexture> GLTextureDummyImpl::getSubImage(
        const Vec2<unsigned int> &l_pos,
        const Vec2<unsigned int> &l_size
    )
    {
        auto sub_image = std::unique_ptr<GLTextureDummyImpl>{new GLTextureDummyImpl{}};
        return std::move(sub_image);
    }
}