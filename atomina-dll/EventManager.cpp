#include "pch.h"
#include "EventManager.h"

namespace ATMA {

	bool EventManager::addEventGroup(EventGroup l_group) {
		if (m_eventGroups.find(l_group.m_name) != m_eventGroups.end())
			return false;

		m_eventGroups[l_group.m_name] = std::shared_ptr<EventGroup>{&l_group};
		return true;
	}

	bool EventManager::removeGroup(EventGroup l_group) {
		auto itr = m_eventGroups.find(l_group.m_name);
		if ( itr == m_eventGroups.end())
			return false;
		m_eventGroups.erase(itr);
		return true;
	}

}