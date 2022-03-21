#include "pch.h"
#include "SysBase.h"

namespace ATMA {


	bool SysBase::addObject(const ObjectId& l_id) {
		if (std::count(m_objects.begin(), m_objects.end(), l_id)) {
			return false;
		}
		m_objects.push_back(l_id);
		return true;

	}

	bool SysBase::hasObject(const ObjectId& l_id) const {
		if (std::count(m_objects.begin(), m_objects.end(), l_id)) {
			return true;
		}else {
			return false;
		}
	}

	bool SysBase::removeObject(const ObjectId& l_id) {
		for (auto it = m_objects.begin(); it != m_objects.end(); it++) {
			if (*it == l_id) {
				m_objects.erase(it);
				return true;
			}
		}
		return false;

	}

	SystemType SysBase::getType() const {
		return m_type;
	}

	bool SysBase::match(const std::bitset<ATConst::OBJECT_BIT_SIZE>& l_bits) const {
		return (m_req ^ l_bits).none();
	}

	void SysBase::purge() {
		m_objects.clear();
	}

}