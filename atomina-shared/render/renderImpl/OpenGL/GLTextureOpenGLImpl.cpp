#include "pch.hpp"
#include "GLTextureOpenGLImpl.hpp"
#include "util/Log.hpp"

namespace ATMA
{
    // constructor with name and filename of resource
    GLTextureOpenGLImpl::GLTextureOpenGLImpl(const std::string &l_fileName): GLTexture(l_fileName)
    {
        glGenTextures(1, &m_bindID);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_bindID);
        glTexStorage2D(GL_TEXTURE_2D, 1, OpenGLImageDataFormat(m_channels), m_width, m_height);
    }

    GLTextureOpenGLImpl::GLTextureOpenGLImpl(): GLTexture()
    {
        glGenTextures(1, &m_bindID);
    }

    GLTextureOpenGLImpl::~GLTextureOpenGLImpl()
    {
        glDeleteTextures(1, &m_bindID);
    }

    void GLTextureOpenGLImpl::bind()
    {
        glBindTexture(GL_TEXTURE_2D, m_bindID);
        glTexSubImage2D(
            GL_TEXTURE_2D,
            0,
            0,
            0,
            m_width,
            m_height,
            OpenGLImageFormat(m_channels),
            GL_UNSIGNED_BYTE,
            m_data
        );
        glGenerateMipmap(GL_TEXTURE_2D); // Generate num_mipmaps number of mipmaps here.
    }

    void GLTextureOpenGLImpl::unbind()
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    std::shared_ptr<GLTexture> GLTextureOpenGLImpl::getSubImage(
        const Vec2<unsigned int> &l_pos,
        const Vec2<unsigned int> &l_size
    )
    {
        auto sub_image = std::unique_ptr<GLTextureOpenGLImpl>{new GLTextureOpenGLImpl{}};
        glBindTexture(GL_TEXTURE_2D, sub_image->getID());
        glTexStorage2D(GL_TEXTURE_2D, 1, OpenGLImageDataFormat(m_channels), l_size.x, l_size.y);
        glCopyImageSubData(
            m_bindID,
            GL_TEXTURE_2D,
            0,
            l_pos.x,
            l_pos.y,
            0,
            sub_image->m_bindID,
            GL_TEXTURE_2D,
            0,
            0,
            0,
            0,
            l_size.x,
            l_size.y,
            1
        );
        return std::move(sub_image);
    }
}