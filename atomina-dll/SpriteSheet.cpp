#include "pch.h"
#include "SpriteSheet.h"

namespace ATMA
{


	SpriteSheet::SpriteSheet(const std::string &l_filename)
	{
		if(!m_sheet.loadFromFile(l_filename))
			throw 1;
	}

	void SpriteSheet::addAnimation(std::shared_ptr<AnimBase> l_anim)
	{
		m_anims[l_anim] = sf::Sprite{m_sheet};
		sf::Vector2i v{static_cast<int>(l_anim->m_width), static_cast<int>(l_anim->m_height)};
		m_anims[l_anim].setTextureRect({{0,0}, v});
	}

	void SpriteSheet::removeAnimation(const std::string & l_name)
	{}

	void SpriteSheet::positionAnimation(const std::string & l_name, const float &l_x, const float &l_y)
	{
		for(auto &anim : m_anims)
		{
			if(anim.first->m_name == l_name)
			{
				sf::Sprite &sprite = anim.second;

				sprite.setPosition({l_x, l_y});
			}
		}
	}

	void SpriteSheet::positionAnimation(const std::string & l_name, const sf::Vector2f & l_pos)
	{}

	void SpriteSheet::update()
	{
		for(auto &anim : m_anims)
		{
			anim.first->update(1.0f);
			auto frame = anim.first->getCurrentFrameId();
			auto &sprite = anim.second;
			sf::Vector2i v{static_cast<int>(sprite.getTextureRect().width * frame), static_cast<int>(sprite.getTextureRect().top)};
			sf::Vector2i size{sprite.getTextureRect().width, sprite.getTextureRect().height};
			sprite.setTextureRect({v, size});
		}
	}

	void SpriteSheet::draw(sf::RenderTarget &target, const sf::RenderStates &states) const
	{
		for(auto &anim : m_anims)
		{
			target.draw(anim.second);
		}
	}


}