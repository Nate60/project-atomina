#include "../../pch.hpp"
#include "SysController.hpp"


namespace ATMA
{

	SysController::SysController(): SysBase(SystemType(System::Controller))
	{
		m_req.set(1);
		m_req.set(3);
	}

	void SysController::update(const float &l_dt)
	{

	}

	void SysController::move(const EventContext &l_e) 
	{

		auto &sfEvent = l_e.m_sfEvent.value();
		auto &context = ATMAContext::getContext();
		for(auto &obj : m_objects)
		{
			std::shared_ptr<AttrTranslatable> obj_comp = context.getAttribute<AttrTranslatable>(obj, AttrType(Attribute::Translatable));
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
				break;
			default:
				break;

			}
		}
	

	}

}

