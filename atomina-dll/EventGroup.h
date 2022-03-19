#pragma once
#include "pch.h"
#include "api.h"
#include "EventContext.h"
#include "EventType.h"
#include "Event.h"

namespace ATMA {

	struct EventGroup {

		EventGroup(const std::string& l_name) : m_name(l_name), m_ec(l_name), m_count(0) {}

		/*
		* Add event to this group of events
		*/
		void groupEvent(EventType l_type, Event l_events);

		std::vector<std::pair<EventType, Event>> m_events;
		std::string m_name;
		EventContext m_ec;
		int m_count;

	};

}