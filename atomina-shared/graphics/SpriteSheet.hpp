#pragma once
#include "../pch.hpp"
#include "../core/api.hpp"
#include "AnimBase.hpp"
#include "../util/Log.hpp"
#include "../util/ATConst.hpp"

namespace ATMA
{

	using Animations = std::unordered_map<std::shared_ptr<AnimBase>, sf::Sprite>;

	class ATMA_API SpriteSheet : public sf::Drawable
	{
	public:

		SpriteSheet();
		SpriteSheet(const std::string &l_filename);

		void addAnimation(std::shared_ptr<AnimBase> l_anim);
		void removeAnimation(const std::string &l_name);
		void positionAnimation(const std::string &l_name, const float &l_x, const float &l_y);
		void positionAnimation(const std::string &l_name, const sf::Vector2f &l_pos);

		void draw(sf::RenderTarget &target, const sf::RenderStates &states = sf::RenderStates::Default) const override;
		void update();

	private:
		Animations m_anims;
		sf::Texture m_sheet;

	};

}