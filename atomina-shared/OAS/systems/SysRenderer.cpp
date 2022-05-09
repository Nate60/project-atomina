#include "../../pch.hpp"
#include "SysRenderer.hpp"

namespace ATMA
{

	void SysRenderer::update(float l_dt)
	{

	}

	void SysRenderer::handleEvent(const ObjectId &l_id, Event &l_event)
	{

	}

	void SysRenderer::notify(const Message &l_message)
	{}

	void SysRenderer::draw(sf::RenderTarget & target, const sf::RenderStates &l_states) const
	{
		auto objMan = m_sysMan.getObjectManager();
		for(auto &obj : m_objects)
		{
			auto pos = objMan->getAttribute<AttrTranslatable>(obj, 1);
			std::shared_ptr<AttrDrawable> drawable = objMan->getAttribute<AttrDrawable>(obj, 2);
			std::shared_ptr<AttrTranslatable> translatable = objMan->getAttribute<AttrTranslatable>(obj, 1);
			drawable->updateScreenPosition(translatable->m_x, translatable->m_y);
			drawable->draw(target);
		}
	}

}