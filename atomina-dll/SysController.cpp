#include "pch.h"
#include "SysController.h"


namespace ATMA
{
	void SysController::update(float l_dt)
	{

	}

	void SysController::handleEvent(const ObjectId &l_id, Event &l_e) 
	{
		if(l_e.m_context.index() == 0)
			return;

		auto &sfEvent = std::get<sf::Event>(l_e.m_context);
		auto objman = m_sysMan.getObjectManager();
		std::shared_ptr<AttrTranslatable> obj_comp = objman->getAttribute<AttrTranslatable>(l_id, Attribute::Translatable);
		auto acceleration = 0.0f;

		if(sfEvent.type == sf::Event::EventType::KeyPressed)
		{
			acceleration = 1.0f;
		}
		else if(sfEvent.type == sf::Event::EventType::KeyReleased)
		{
			acceleration = 0;
		}

		switch(sfEvent.key.code)
		{
		case sf::Keyboard::W:
			obj_comp->m_dy = -acceleration;
			break;
		case sf::Keyboard::S:
			obj_comp->m_dy = acceleration;
		}

	}
	void SysController::notify(const Message &l_message)
	{}
}

