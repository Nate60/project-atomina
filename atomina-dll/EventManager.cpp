#include "pch.h"
#include "EventManager.h"

namespace ATMA {

	bool EventManager::addEventGroup(EventGroup l_group) {
		if (eventGroups_.find(l_group.name_) != eventGroups_.end())
			return false;

		eventGroups_[l_group.name_] = &l_group;
		return true;
	}

	bool EventManager::removeGroup(EventGroup l_group) {
		auto itr = eventGroups_.find(l_group.name_);
		if ( itr == eventGroups_.end())
			return false;
		eventGroups_.erase(itr);
		return true;
	}

}