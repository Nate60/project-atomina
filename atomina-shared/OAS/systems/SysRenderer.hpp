#pragma once
#include "../../pch.hpp"
#include "../../core/api.hpp"
#include "../SysBase.hpp"
#include "../attributes/AttrTranslatable.hpp"
#include "../attributes/AttrDrawable.hpp"
#include "../System.hpp"

namespace ATMA
{

	class ATMA_API SysRenderer: public SysBase, public sf::Drawable
	{
	public:
		SysRenderer();

		virtual void update(const float &l_dt) override;

		virtual void draw(sf::RenderTarget &target, const sf::RenderStates &l_states = sf::RenderStates::Default) const override;

	};

}