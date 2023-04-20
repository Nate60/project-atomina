#include "pch.hpp"
#include "Font.hpp"

namespace ATMA
{

    // constructor specifying name
    Font::Font(const std::string &l_name): Resource(l_name)
    {
        Texture fontTexture{l_name, "res\\defaultFont.png"};
        fontTexture.bind();
        for(char i = 0; i < '~'; i++)
        {
            m_characters[i] = fontTexture.getSubImage({i % 11, i / 11}, {32, 32});
        }
        fontTexture.unbind();
    }

    // constructor specifying name and filename;
    Font::Font(const std::string &l_name, const std::string &l_filename):
        Resource(l_name, l_filename)
    {
        Texture fontTexture{l_name, l_filename};
        fontTexture.bind();
        for(char i = 0; i <= '~'; i++)
        {
            m_characters[i] = fontTexture.getSubImage({(i % 11) * 32, (i / 11) * 32}, {32, 32});
        }
        fontTexture.unbind();
    }

    void Font::bindCharacter(const char &l_character)
    {
        m_characters[l_character]->bind();
    }

    Font::~Font() {}
}