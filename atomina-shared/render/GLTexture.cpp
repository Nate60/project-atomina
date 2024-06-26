#include "pch.hpp"
#include "GLTexture.hpp"
#ifdef ATMA_OPENGL
#    include "renderImpl/OpenGL/GLTextureOpenGLImpl.hpp"
#    define __ATMAMAKEGLTEXTURE(textureData)                                                       \
        return std::make_shared<GLTextureOpenGLImpl>(textureData)
#else
#    include "renderImpl/Dummy/GLTextureDummyImpl.hpp"
#    define __ATMAMAKEGLTEXTURE(textureData)                                                       \
        return std::make_shared<GLTextureDummyImpl>(textureData)
#endif

namespace ATMA
{

    GLTexture::GLTexture(const Path &l_filePath)
    {
        ATMA_ENGINE_TRACE("Creating GL Texture");
        m_data = stbi_load(l_filePath.toString().c_str(), &m_width, &m_height, &m_channels, 0);
        ATMA_ENGINE_INFO("stb image loaded image with {0} channels from {1}", m_channels, l_filePath.toString());
    }

    GLTexture::GLTexture()
    {
        m_data = 0;
        m_width = 0;
        m_height = 0;
        m_channels = 0;
        ATMA_ENGINE_TRACE("Creating GL Texture");
    }

    GLTexture::~GLTexture() 
    {
        ATMA_ENGINE_TRACE("Deleting GL Texture");
    }

    const unsigned int &GLTexture::getID() const
    {
        return m_bindID;
    }

    std::shared_ptr<GLTexture> GLTexture::makeTexture(const Path &l_filePath)
    {
        __ATMAMAKEGLTEXTURE(l_filePath);
    }

}