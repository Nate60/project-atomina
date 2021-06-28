#pragma once
#include "pch.h"
#include "api.h"
#include "EventContext.h"
#include "EventType.h"
#include "Event.h"

namespace ATMA {

	struct EventGroup {

		EventGroup(const std::string& l_name) : name_(l_name), ec_(l_name), count_(0) {}

		/*
		* Add event to this group of events
		*/
		void groupEvent(EventType l_type, Event l_events);

		std::vector<std::pair<EventType, Event>> events_;
		std::string name_;
		EventContext ec_;
		int count_;

	};

}