#include "pch.hpp"
#include "TextureGLADImpl.hpp"
#include "util/Log.hpp"

namespace ATMA
{

    TextureGLADImpl::TextureGLADImpl(const std::string &l_name): Texture(l_name)
    {
        glGenTextures(1, &m_bindID);
    }

    // constructor with name and filename of resource
    TextureGLADImpl::TextureGLADImpl(const std::string &l_name, const std::string &l_fileName):
        Texture(l_name, l_fileName)
    {
        glGenTextures(1, &m_bindID);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_bindID);
        glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA16, m_width, m_height);
    }

    TextureGLADImpl::~TextureGLADImpl()
    {
        glDeleteTextures(1, &m_bindID);
    }

    void TextureGLADImpl::bind()
    {
        glBindTexture(GL_TEXTURE_2D, m_bindID);
        glTexSubImage2D(
            GL_TEXTURE_2D, 0, 0, 0, m_width, m_height, GL_RGBA, GL_UNSIGNED_BYTE, m_data
        );
        glGenerateMipmap(GL_TEXTURE_2D); // Generate num_mipmaps number of mipmaps here.
    }

    void TextureGLADImpl::unbind()
    {

        glBindTexture(GL_TEXTURE_2D, 0);
    }

    std::shared_ptr<Texture>
    TextureGLADImpl::getSubImage(const Vec2<unsigned int> &l_pos, const Vec2<unsigned int> &l_size)
    {
        auto sub_image = std::make_unique<TextureGLADImpl>("subimage");
        glGenTextures(1, &(sub_image->m_bindID));
        glBindTexture(GL_TEXTURE_2D, sub_image->getID());
        glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA16, l_size.x, l_size.y);
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