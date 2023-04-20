#include "pch.hpp"
#include "TextureBindingGLADImpl.hpp"
#include "util/Log.hpp"

namespace ATMA
{
    // constructor with name and filename of resource
    TextureBindingGLADImpl::TextureBindingGLADImpl(const std::string &l_fileName):
        TextureBinding(l_fileName)
    {
        glGenTextures(1, &m_bindID);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_bindID);
        glTexStorage2D(GL_TEXTURE_2D, 1, GLADImageDataFormat(m_channels), m_width, m_height);
    }

    TextureBindingGLADImpl::TextureBindingGLADImpl(): TextureBinding()
    {
        glGenTextures(1, &m_bindID);
    }

    TextureBindingGLADImpl::~TextureBindingGLADImpl()
    {
        glDeleteTextures(1, &m_bindID);
    }

    void TextureBindingGLADImpl::bind()
    {
        glBindTexture(GL_TEXTURE_2D, m_bindID);
        glTexSubImage2D(
            GL_TEXTURE_2D,
            0,
            0,
            0,
            m_width,
            m_height,
            GLADImageFormat(m_channels),
            GL_UNSIGNED_BYTE,
            m_data
        );
        glGenerateMipmap(GL_TEXTURE_2D); // Generate num_mipmaps number of mipmaps here.
    }

    void TextureBindingGLADImpl::unbind()
    {

        glBindTexture(GL_TEXTURE_2D, 0);
    }

    std::shared_ptr<TextureBinding> TextureBindingGLADImpl::getSubImage(
        const Vec2<unsigned int> &l_pos,
        const Vec2<unsigned int> &l_size
    )
    {
        auto sub_image = std::unique_ptr<TextureBindingGLADImpl>{new TextureBindingGLADImpl{}};
        glBindTexture(GL_TEXTURE_2D, sub_image->getID());
        glTexStorage2D(GL_TEXTURE_2D, 1, GLADImageDataFormat(m_channels), l_size.x, l_size.y);
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