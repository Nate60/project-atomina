#include "pch.hpp"
#include "resource/Resource.hpp"
#include "GLTexture.hpp"
#ifdef ATMA_OPENGL
#    include "renderImpl/OpenGL/GLTextureOpenGLImpl.hpp"
#    define __ATMAMAKEGLTEXTURE(textureData) return std::make_shared<GLTextureOpenGLImpl>(textureData)
#else
#    include "renderImpl/Dummy/GLTextureDummyImpl.hpp"
#    define __ATMAMAKEGLTEXTURE(textureData) return std::make_shared<GLTextureDummyImpl>(textureData)
#endif

namespace ATMA
{

    void Texture::operator=(const Texture &l_texture)
    {
        m_name = l_texture.m_name;
        m_path = l_texture.m_path;
        m_type = l_texture.m_type;
        m_width = l_texture.m_width;
        m_height = l_texture.m_height;
        m_channels = l_texture.m_channels;
        m_proj = l_texture.m_proj;
        m_data = l_texture.m_data;
    }

    void Texture::operator=(Texture &&l_texture)
    {
        m_name = std::move(l_texture.m_name);
        m_path = std::move(l_texture.m_path);
        m_type = std::move(l_texture.m_type);
        m_width = std::move(l_texture.m_width);
        m_height = std::move(l_texture.m_height);
        m_channels = std::move(l_texture.m_channels);
        m_proj = std::move(l_texture.m_proj);
        m_data = std::move(l_texture.m_data);
    }

    const int &Texture::width() const
    {
        return m_width;
    }

    const int &Texture::height() const
    {
        return m_height;
    }

    const int &Texture::channels() const
    {
        return m_channels;
    }

    const Mat3<float> &Texture::proj() const
    {
        return m_proj;
    }

    const unsigned char *const Texture::data() const
    {
        return m_data;
    }

    GLTexture::GLTexture(const Texture &l_texture): LoadedResource(), m_texture(l_texture) {}

    GLTexture::GLTexture(const GLTexture &l_texture): LoadedResource(), m_texture(l_texture.m_texture)
    {
        m_bindID = l_texture.m_bindID;
        m_indexBuf = l_texture.m_indexBuf;
        m_vertBuf = l_texture.m_vertBuf;
        m_vertArr = l_texture.m_vertArr;
    }

    GLTexture::GLTexture(GLTexture &&l_texture): LoadedResource(), m_texture(std::move(l_texture.m_texture))
    {
        m_bindID = std::move(l_texture.m_bindID);
        m_indexBuf = std::move(l_texture.m_indexBuf);
        m_vertBuf = std::move(l_texture.m_vertBuf);
        m_vertArr = std::move(l_texture.m_vertArr);
    }

    GLTexture::~GLTexture() {}

    const unsigned int &GLTexture::getID() const
    {
        return m_bindID;
    }

    void GLTexture::operator=(const GLTexture &l_texture)
    {
        m_texture = l_texture.m_texture;
        m_bindID = l_texture.m_bindID;
        m_indexBuf = l_texture.m_indexBuf;
        m_vertBuf = l_texture.m_vertBuf;
        m_vertArr = l_texture.m_vertArr;
    }

    void GLTexture::operator=(GLTexture &&l_texture)
    {
        m_texture = std::move(l_texture.m_texture);
        m_bindID = std::move(l_texture.m_bindID);
        m_indexBuf = std::move(l_texture.m_indexBuf);
        m_vertBuf = std::move(l_texture.m_vertBuf);
        m_vertArr = std::move(l_texture.m_vertArr);
    }

    std::shared_ptr<GLTexture> GLTexture::makeTexture(const Texture &l_texture)
    {
        __ATMAMAKEGLTEXTURE(l_texture);
    }

}
