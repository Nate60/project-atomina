#include "pch.hpp"
#include "TextureGLADImpl.hpp"

namespace ATMA
{

    TextureGLADImpl::TextureGLADImpl(const std::string &l_name): Texture(l_name) {}

    // constructor with name and filename of resource
    TextureGLADImpl::TextureGLADImpl(const std::string &l_name, const std::string &l_fileName):
        Texture(l_name, l_fileName)
    {
    }

    TextureGLADImpl::~TextureGLADImpl()
    {
        glDeleteTextures(1, &m_bindID);
    }

    void TextureGLADImpl::bind()
    {
        glGenTextures(1, &m_bindID);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_bindID);
        glTexImage2D(
            GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_data
        );
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    void TextureGLADImpl::unbind()
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

}