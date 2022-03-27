#pragma once
#include "pch.h"
#include "api.h"
#include "Event.h"

namespace ATMA {

	using EventType = unsigned int;
	using EventContainer = std::vector<EventType>;

	class ATMA_API Binding
	{
	public:
		EventContainer m_events;
		int m_count;
	};

}

