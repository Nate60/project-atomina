#include "SystemManager.h"

namespace ATMA {

	void SystemManager::update(float l_dt) {
		for (auto& system : systems_) {
			system.second->update(l_dt);
		}
	}

	void SystemManager::objectModified(const ObjectId& l_id, const std::bitset<ATConst::OBJECT_BIT_SIZE> l_bits) {
		for (auto& it : systems_) {
			auto& system = it.second;
			if (system->match(l_bits)) {
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
		for (auto &system : systems_) {
			system.second->removeObject(l_id);
		}
	}

	void SystemManager::purgeObjects() {
		for (auto& system : systems_) {
			system.second->purge();
		}
	}

	void SystemManager::purgeSystems() {
		systems_.clear();
	}

}