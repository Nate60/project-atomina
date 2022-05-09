#include "../pch.hpp"
#include "SystemManager.hpp"

namespace ATMA {

	SystemManager::SystemManager(): m_objMan(new ObjectManager{})
	{}

	void SystemManager::update(float l_dt) {
		for (auto& system : m_systems) {
			system.second->update(l_dt);
		}
	}

	void SystemManager::objectModified(const ObjectId& l_id, const std::bitset<ATConst::OBJECT_BIT_SIZE> l_bits) {
		for (auto& it : m_systems) {
			if (auto system = it.second; system->match(l_bits)) {
				system->addObject(l_id);
			}
			else {
				system->removeObject(l_id);
			}
		}
	}

	void SystemManager::handleEvents() {
		for(auto &object_event : m_object_event_queue)
		{
			for(auto &system : m_systems)
			{
				if(system.second->hasObject(object_event.first))
				{
					for(auto &e : object_event.second)
					{
						system.second->handleEvent(object_event.first, e);
					}
					
				}
			}
		}
	}

	void SystemManager::addEvent(const ObjectId  &l_id, Event& l_event)
	{
		if(auto queue = m_object_event_queue.find(l_id); queue == m_object_event_queue.end())
		{
			m_object_event_queue[l_id] = std::vector<Event>{l_event};
		}
		else
		{
			m_object_event_queue[l_id].push_back(l_event);
		}

	}

	void SystemManager::removeObject(const ObjectId& l_id) {
		ATMA_ENGINE_INFO("Removing Object ID {:d} from all systems", l_id);
		for (auto &system : m_systems) {
			system.second->removeObject(l_id);
		}
	}

	void SystemManager::purgeObjects() {
		ATMA_ENGINE_INFO("Purging objects from all systems");
		for (auto& system : m_systems) {
			system.second->purge();
		}
	}

	void SystemManager::purgeSystems() {
		ATMA_ENGINE_INFO("Purging systems from SystemManager");
		m_systems.clear();
	}

}