#include "pch.hpp"
#include "Font.hpp"

namespace ATMA
{

    Font::Font(const std::string &l_name): Resource(l_name)
    {
        //TODO: ATMA-67
    }

    Font::Font(const std::string &l_name, const Path &l_path):
        Resource(l_name, l_path),
        m_fontTexture(GLTexture::makeTexture(l_path))
    {
    }

    Font::~Font() {}

}