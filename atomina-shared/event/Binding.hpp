#pragma once
#include "../pch.hpp"
#include "../core/api.hpp"
#include "Event.hpp"

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

