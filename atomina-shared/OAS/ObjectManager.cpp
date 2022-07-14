#include "../pch.hpp"
#include "ObjectManager.hpp"

namespace ATMA {

	ATMA_API ObjectManager::ObjectManager() {
	}

	ATMA_API ObjectManager::~ObjectManager() {

	}

	ObjectId ObjectManager::createObject(const std::bitset<ATConst::OBJECT_BIT_SIZE> &l_bits){

		//unordered map uses unique ids so last id needs to be updated atomically

		std::lock_guard<std::mutex> lock{m_mtx};

		auto id = m_lastId++;

		for (int i = 0; i < ATConst::OBJECT_BIT_SIZE; i++) {

			if (l_bits[i]) {
				addAttribute(id, Attribute(i));
			}

		}

		ATMA_ENGINE_INFO("Created object with id {:d}", id);
		if(m_lastId < id)
			throw std::overflow_error("object id count overflow");
		return id;

	}

	ObjectId ObjectManager::createObject() {


		const std::lock_guard<std::mutex> lock{m_mtx};

		auto id = m_lastId++;

		ATMA_ENGINE_INFO("Created object with id {:d}", id);
		if(m_lastId < id)
			throw std::overflow_error("object id count overflow");
		return id;
	
	}

	bool ObjectManager::removeObject(const ObjectId &l_id) {

		if (m_objects.erase(l_id) > 0) {
			ATMA_ENGINE_INFO("erased object with id {0:d}", l_id);
			return true;
		}
		else {
			ATMA_ENGINE_WARN("unable to erase object with id {0:d}", l_id);
			return false;
		}

	}

	bool ObjectManager::addAttribute(const ObjectId &l_id, const Attribute &l_attr)
	{
		return addAttribute(l_id, static_cast<AttributeType>(l_attr));
	}

	bool ObjectManager::addAttribute(const ObjectId &l_id, const AttributeType &l_attr) {

		//if an object is added that is greater than the highest id, create object may override it in the future
		if (l_id > m_lastId) {
			ATMA_ENGINE_WARN("unable to add attribute {0:d} as object id {1:d} does not exist", l_attr, l_id);
			return false;
		}

		if (m_objects[l_id].first[l_attr]) {
			ATMA_ENGINE_WARN("unable to add attribute {0:d} as object id {1:d} already is {0:d}", l_attr, l_id);
			return false;
		}

		if (m_attrFactory.find(l_attr) == m_attrFactory.end()) {
			ATMA_ENGINE_WARN("unable to add attribute {0:d} as there is no factory for it", l_attr);
			return false;
		}

		m_objects[l_id].first.set(l_attr);
		std::shared_ptr<AttrBase> attr = m_attrFactory[l_attr]();
		auto pair = std::pair<int, std::shared_ptr<AttrBase>>(l_attr, attr);
		m_objects[l_id].second.insert(pair);
		
		ATMA_ENGINE_INFO("object id {1:d} is now {0:d}", l_attr, l_id);

		return true;

	}

	bool ObjectManager::removeAttribute(const ObjectId &l_id, const Attribute &l_attr)
	{
		return removeAttribute(l_id, static_cast<AttributeType>(l_attr));
	}

	bool ObjectManager::removeAttribute(const ObjectId &l_id, const AttributeType &l_attr) {

		if (m_objects.find(l_id) == m_objects.end()) {
			ATMA_ENGINE_WARN("unable to remove attribute {0:d} as object id {1:d} does not exist", l_attr, l_id);
			return false;
		}


		if (!m_objects[l_id].first[l_attr]) {
			ATMA_ENGINE_WARN("unable to remove attribute {0:d} as object id {1:d} is not {0:d}", l_attr, l_id);
			return false;
		}

		m_objects[l_id].first.reset(l_attr);
		m_objects[l_id].second.erase(l_attr);

		ATMA_ENGINE_INFO("object id {1:d} is no longer {0:d}", l_attr, l_id);

		return true;

	}


	bool ObjectManager::hasAttribute(const ObjectId &l_id, const Attribute &l_attr)
	{
		return hasAttribute(l_id, static_cast<AttributeType>(l_attr));
	}

	bool ObjectManager::hasAttribute(const ObjectId &l_id, const AttributeType &l_attr) {

		if (m_objects.count(l_id) <= 0)
			return false;

		return m_objects[l_id].second.count(l_attr) > 0;


	}

	void ObjectManager::purge() {

		ATMA_ENGINE_INFO("Object Manager has been purged");

		m_objects.clear();
		m_attrFactory.clear();
		m_lastId = 0;

	}


}