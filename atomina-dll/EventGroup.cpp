#include "pch.h"
#include "EventGroup.h"

namespace ATMA {

	void EventGroup::groupEvent(ATMA::EventType l_type, Event l_event = Event()) {
		events_.emplace_back(std::pair<ATMA::EventType, Event>(l_type, l_event));
	}
}