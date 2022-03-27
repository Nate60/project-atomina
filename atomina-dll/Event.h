#pragma once
#include "pch.h"
#include "api.h"
#include "EventContext.h"

namespace ATMA
{

	using EventType = unsigned int;

	struct ATMA_API Event
	{
		Event(const std::string &l_name) : m_type(0), m_context(l_name)
		{}

		Event(EventContext &l_ctx): m_type(0), m_context(l_ctx)
		{}

		Event(const EventType &l_type, const std::string &l_name): m_type(l_type), m_context(l_name)
		{}

		Event(const EventType &l_type, EventContext &l_ctx): m_type(l_type), m_context(l_ctx)
		{}

		Event(const EventType &l_type, sf::Event &l_e): m_type(l_type), m_context(l_e)
		{}

		Event(const Event &e): m_type(e.m_type), m_context(e.m_context)
		{}

		Event &operator=(const Event &e)
		{
			m_type = e.m_type;
			m_context = e.m_context;
			return *this;
		}

		EventType m_type;
		std::variant<EventContext, sf::Event> m_context;

	
		
	};
}
