#pragma once
#include "pch.h"
#include "api.h"
#include "AttrBase.h"
#include "SpriteSheet.h"
#include "SysUtil.h"
#include "AnimIdle.h"


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

	protected:
		SpriteSheet m_sheet;

	};

}