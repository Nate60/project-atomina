#include "pch.h"
#include "SysTranslator.h"

namespace ATMA {

	SysTranslator::SysTranslator(const System& l_type, SystemManager* l_sysMan) : SysBase(l_type, l_sysMan) {
		std::bitset<ATConst::OBJECT_BIT_SIZE> bits;
		bits.set((int)Attribute::Translatable);
		req_ = bits;
	}

	SysTranslator::~SysTranslator() {

	}

	void SysTranslator::notify(const Message& l_message) {

	}

	void SysTranslator::update(float l_dt) {
		ObjectManager* objMan = sysMan_->getObjectManager();
		for (auto& obj : objects_) {
			AttrTranslatable* attr = objMan->getAttribute<AttrTranslatable>(obj, Attribute::Translatable);
			attr->x_ += attr->dx_ * l_dt;
			attr->y_ += attr->dy_ * l_dt;
		}
	}

}