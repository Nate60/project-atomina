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

    GLTexture::GLTexture(const Texture &l_texture): m_texture(l_texture), LoadedResource()
    {
    }

    GLTexture::~GLTexture() 
    {
    }

    const unsigned int &GLTexture::getID() const
    {
        return m_bindID;
    }

    std::shared_ptr<GLTexture> GLTexture::makeTexture(const Texture &l_texture)
    {
        __ATMAMAKEGLTEXTURE(l_texture);
    }

}