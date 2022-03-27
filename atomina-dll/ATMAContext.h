#pragma once
#include "pch.h"
#include "api.h"

namespace ATMA
{

	class EventManager;
	class SystemManager;

	struct ATMA_API ATMAContext
	{

		std::shared_ptr<EventManager> m_event_manager{nullptr};
		std::shared_ptr<SystemManager> m_system_manager{nullptr};


	};

}