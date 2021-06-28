#include "pch.h"
#include "ObjectManager.h"

namespace ATMA {

	ATMA_API ObjectManager::ObjectManager() {
		lastId_ = 0;
	}

	ATMA_API ObjectManager::~ObjectManager() {

	}

	int ObjectManager::createObject(const std::bitset<ATConst::OBJECT_BIT_SIZE>& l_bits){

		//unordered map uses unique ids so last id needs to be updated atomically

		mtx_.lock();

		auto id = lastId_++;

		mtx_.unlock();

		for (int i = 0; i < ATConst::OBJECT_BIT_SIZE; i++) {

			if (l_bits[i]) {
				addAttribute(id, Attribute(i));
			}

		}

		ATMA_ENGINE_INFO("created object with id {:d}", id);

		return id;

	}

	int ObjectManager::createObject() {

		mtx_.lock();

		auto id = lastId_++;

		mtx_.unlock();

		return id;

	}

	bool ObjectManager::removeObject(const ObjectId& l_id) {

		if (objects_.erase(l_id) > 0) {
			ATMA_ENGINE_INFO("erased object with id {0:d}", l_id);
			return true;
		}
		else {
			ATMA_ENGINE_WARN("unable to erase object with id {0:d}", l_id);
			return false;
		}

	}

	bool ObjectManager::addAttribute(const ObjectId& l_id, const Attribute& l_attr) {

		if (l_id > lastId_) {
			ATMA_ENGINE_WARN("unable to add attribute {0:d} as object id {1:d} does not exist", (int)l_attr, l_id);
			return false;
		}

		if (objects_[l_id].first[(int)l_attr]) {
			ATMA_ENGINE_WARN("unable to add attribute {0:d} as object id {1:d} already is {0:d}", (int)l_attr, l_id);
			return false;
		}

		objects_[l_id].first.set((int)l_attr);

		if (attrFactory_.count(l_attr) == 0) {
			ATMA_ENGINE_WARN("unable to add attribute {0:d} as there is no factory for it", (int)l_attr);
			return false;
		}

		AttrBase* attr = attrFactory_[l_attr]();
		auto pair = std::pair<int, AttrBase*>((int)l_attr, attr);
		objects_[l_id].second.insert(pair);
		
		ATMA_ENGINE_INFO("object id {1:d} is now {0:d}", l_attr, l_id);

		return true;

	}

	bool ObjectManager::removeAttribute(const ObjectId& l_id, const Attribute& l_attr) {

		if (objects_.count(l_id) <= 0) {
			ATMA_ENGINE_WARN("unable to remove attribute {0:d} as object id {1:d} does not exist", (int)l_attr, l_id);
			return false;
		}


		if (!objects_[l_id].first[(int)l_attr]) {
			ATMA_ENGINE_WARN("unable to remove attribute {0:d} as object id {1:d} is not {0:d}", (int)l_attr, l_id);
			return false;
		}

		objects_[l_id].first.reset((int)l_attr);
		objects_[l_id].second.erase((int)l_attr);

		ATMA_ENGINE_INFO("object id {1:d} is no longer {0:d}", (int)l_attr, l_id);

		return true;

	}

	bool ObjectManager::hasAttribute(const ObjectId& l_id, const Attribute& l_attr) {

		if (objects_.count(l_id) <= 0)
			return false;

		return objects_[l_id].second.count((int)l_attr) > 0;


	}

	void ObjectManager::purge() {

		ATMA_ENGINE_INFO("Object Manager has been purged");

		objects_.clear();
		attrFactory_.clear();
		lastId_ = 0;

	}


}