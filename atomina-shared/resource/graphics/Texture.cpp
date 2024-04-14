#include "pch.hpp"
#include "Texture.hpp"

namespace ATMA
{
    Texture::Texture(const std::string &l_name): Resource(l_name) {}

    Texture::Texture(const std::string &l_name, const Path &l_path):
        Resource(l_name, l_path),
        m_self(GLTexture::makeTexture(l_path))
    {
    }

    Texture::~Texture() {}
}
