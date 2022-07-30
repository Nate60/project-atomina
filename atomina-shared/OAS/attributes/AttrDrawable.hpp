#pragma once
#include "../../pch.hpp"
#include "../../core/api.hpp"
#include "../AttrBase.hpp"
#include "../../graphics/SpriteSheet.hpp"
#include "../../file/FileFuncs.hpp"
#include "../../graphics/animation/AnimIdle.hpp"


namespace ATMA
{

	class ATMA_API AttrDrawable: public AttrBase
	{
	public:
		AttrDrawable();
		~AttrDrawable();

		virtual void updateScreenPosition(const float &l_x, const float &l_y);
		virtual void draw(sf::RenderTarget &l_target);
		virtual void readIn(std::stringstream &l_stream) override;

		
		SpriteSheet m_sheet;

	};

}