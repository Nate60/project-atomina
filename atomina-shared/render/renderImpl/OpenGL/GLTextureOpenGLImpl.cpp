#include "pch.hpp"
#include "GLTextureOpenGLImpl.hpp"
#include "util/Log.hpp"

namespace ATMA
{
    // constructor with name and filename of resource
    GLTextureOpenGLImpl::GLTextureOpenGLImpl(const Texture &l_texture): GLTexture(l_texture)
    {
        m_vertArr = VertexArray::makeBuffer({
            {2, 8, 0}, //  screen x,y
            {4, 8, 2}, //  colour r,b,g,a
            {2, 8, 6}  //  texture x,y
        });
        m_vertBuf = VertexBuffer::makeBuffer({
            0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, // vertex 1
            0.5f,  -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // vertex 2
            -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, // vertex 3
            -0.5f, 0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f  // vertex 4
        });
        m_indexBuf = IndexBuffer::makeBuffer({0, 1, 2, 0, 2, 3});
        m_vertArr->bind();
        m_vertBuf->bind();
        m_indexBuf->bind();
        m_vertArr->bindLayout();
        glGenTextures(1, &m_bindID);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_bindID);
        glTexStorage2D(
            GL_TEXTURE_2D, 1, OpenGLImageDataFormat(m_texture.channels()), m_texture.width(), m_texture.height()
        );
        // when scaling up use nearest pixel instead of sampling
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
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
            m_texture.width(),
            m_texture.height(),
            OpenGLImageFormat(m_texture.channels()),
            GL_UNSIGNED_BYTE,
            m_texture.data()
        );
        glGenerateMipmap(GL_TEXTURE_2D); // Generate num_mipmaps number of mipmaps here.
    }

    void GLTextureOpenGLImpl::unbind()
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    std::shared_ptr<GLTexture>
    GLTextureOpenGLImpl::getSubImage(const Vec2<unsigned int> &l_pos, const Vec2<unsigned int> &l_size)
    {
        auto sub_image = std::unique_ptr<GLTextureOpenGLImpl>{new GLTextureOpenGLImpl{m_texture}};
        glBindTexture(GL_TEXTURE_2D, sub_image->getID());
        // glTexStorage2D(GL_TEXTURE_2D, 1, OpenGLImageDataFormat(m_channels), l_size.x, l_size.y);
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
