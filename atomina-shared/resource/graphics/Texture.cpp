#include "pch.hpp"
#include "Texture.hpp"

namespace ATMA
{
    Texture::Texture(const std::string &l_name): Resource(l_name)
    {
        m_data = stbi_load("res/shaggysheet.png", &m_width, &m_height, &m_channels, 0);
    }

    Texture::Texture(const std::string &l_name, const std::string &l_filename):
        Resource(l_name, l_filename)
    {
        m_data = stbi_load(l_filename.c_str(), &m_width, &m_height, &m_channels, 0);
    }

    Texture::~Texture() {}

    void Texture::bind() {}

    void Texture::unbind() {}

    std::shared_ptr<Texture>
    Texture::getSubImage(const Vec2<unsigned int> &l_pos, const Vec2<unsigned int> &l_size)
    {
        return nullptr;
    }

    const unsigned int &Texture::getID() const
    {
        return m_bindID;
    }

}