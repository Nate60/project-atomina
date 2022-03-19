#include "pch.h"
#include "SystemManager.h"

namespace ATMA {

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