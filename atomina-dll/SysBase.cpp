#include "pch.h"
#include "SysBase.h"

namespace ATMA {


	bool SysBase::addObject(const ObjectId& l_id) {
		if (std::count(objects_.begin(), objects_.end(), l_id)) {
			return false;
		}
		objects_.push_back(l_id);
		return true;

	}

	bool SysBase::hasObject(const ObjectId& l_id) const {
		if (std::count(objects_.begin(), objects_.end(), l_id)) {
			return true;
		}else {
			return false;
		}
	}

	bool SysBase::removeObject(const ObjectId& l_id) {
		for (auto it = objects_.begin(); it != objects_.end(); it++) {
			if (*it == l_id) {
				objects_.erase(it);
				return true;
			}
		}
		return false;

	}

	System SysBase::getType() const {
		return type_;
	}

	bool SysBase::match(const std::bitset<ATConst::OBJECT_BIT_SIZE>& l_bits) const {
		return (req_ ^ l_bits).none();
	}

	void SysBase::purge() {
		objects_.clear();
	}

}