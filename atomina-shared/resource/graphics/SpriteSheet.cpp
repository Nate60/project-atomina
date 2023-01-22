#include "pch.hpp"
#include "SpriteSheet.hpp"
#include <SFML/Graphics/Rect.hpp>

namespace ATMA
{

    SpriteSheet::SpriteSheet(const std::string &l_name): Resource(l_name)
    {
        sf::Image img;
        img.create({2u, 2u}, ATConst::DEFAULT_PIXELS);
       /* if(!m_sheet.loadFromImage(img))
            throw ResourceAcquisitionException("SpriteSheet with name " + l_name + " was unable to be created from default image");
        m_sheet.setRepeated(true);*/
    }

    SpriteSheet::SpriteSheet(const std::string &l_name, const std::string &l_filename): Resource(l_name, l_filename)
    {
        //if(!m_sheet.loadFromFile(l_filename))
        //    throw ResourceAcquisitionException("SpriteSheet with name: " + l_name
        //                                           + " was unable to be created from file: " + l_filename
        //    );
    }

    SpriteSheet::~SpriteSheet() 
    {
        
    }

    void SpriteSheet::updateSprite(const std::unique_ptr<AnimBase> &l_anim, sf::Sprite &l_sprite)
    {
        //l_sprite.setTexture(m_sheet);
        //int x =
        //    l_anim->getCurrentFrameId() * l_anim->m_width + l_anim->m_startFrame * l_anim->m_width;
        //int y = l_anim->m_sheetLine * l_anim->m_height;
        //l_sprite.setTextureRect({
        //    sf::Vector2i{                                x,                                  y},
        //    sf::Vector2i{static_cast<int>(l_anim->m_width), static_cast<int>(l_anim->m_height)}
        //});
    }

}