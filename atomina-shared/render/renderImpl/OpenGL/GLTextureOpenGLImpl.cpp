#include "pch.hpp"
#include "GLTextureOpenGLImpl.hpp"
#include "util/Log.hpp"

namespace ATMA
{
    // constructor with name and filename of resource
    GLTextureOpenGLImpl::GLTextureOpenGLImpl(const Texture &l_texture): GLTexture(l_texture)
    {
        ATMA_ENGINE_TRACE("Creating OPEN GL Texture");
        m_vertArr = VertexArray::makeBuffer({
            {3, 8, 0},
            {3, 8, 3},
            {2, 8, 6}
        });
        m_vertBuf = VertexBuffer::makeBuffer({1.0f,  1.0f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
                                    1.0f,  -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
                                    -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
                                    -1.0f, 1.0f,  0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f});
        m_indexBuf = IndexBuffer::makeBuffer({0, 1, 2, 0, 2, 3});
        m_vertArr->bind();
        m_vertBuf->bind();
        m_indexBuf->bind();
        m_vertArr->bindLayout();
        glGenTextures(1, &m_bindID);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_bindID);
        glTexStorage2D(GL_TEXTURE_2D, 1, OpenGLImageDataFormat(m_texture.m_channels), m_texture.m_width, m_texture.m_height);
    }

    GLTextureOpenGLImpl::~GLTextureOpenGLImpl()
    {
        ATMA_ENGINE_TRACE("Deleting OPEN GL Texture");
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
            m_texture.m_width,
            m_texture.m_height,
            OpenGLImageFormat(m_texture.m_channels),
            GL_UNSIGNED_BYTE,
            m_texture.m_data
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
        auto sub_image = std::unique_ptr<GLTextureOpenGLImpl>{new GLTextureOpenGLImpl{m_texture}};
        glBindTexture(GL_TEXTURE_2D, sub_image->getID());
        //glTexStorage2D(GL_TEXTURE_2D, 1, OpenGLImageDataFormat(m_channels), l_size.x, l_size.y);
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