#include "pch.hpp"
#include "TextureBinding.hpp"

namespace ATMA
{

    TextureBinding::TextureBinding(const std::string &l_filename)
    {
        m_data = stbi_load(l_filename.c_str(), &m_width, &m_height, &m_channels, 0);
        ATMA_ENGINE_INFO("stb image loaded image with {0} channels", m_channels);
    }

    TextureBinding::TextureBinding()
    {
        m_data = 0;
        m_width = 0;
        m_height = 0;
        m_channels = 0;
    }

    TextureBinding::~TextureBinding() {}

    const unsigned int &TextureBinding::getID() const
    {
        return m_bindID;
    }

}