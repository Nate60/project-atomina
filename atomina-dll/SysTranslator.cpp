#include "pch.h"
#include "SysTranslator.h"

namespace ATMA {

	SysTranslator::SysTranslator(const SystemType& l_type, SystemManager &l_man) : SysBase(l_type, l_man) {
		std::bitset<ATConst::OBJECT_BIT_SIZE> bits;
		bits.set((int)Attribute::Translatable);
		m_req = bits;
	}

	SysTranslator::~SysTranslator() {

	}

	void SysTranslator::notify(const Message& l_message) {

	}

	void SysTranslator::update(float l_dt) {
		std::shared_ptr<ObjectManager> objMan = m_sysMan.getObjectManager();
		for (auto& obj : m_objects) {
			if(!objMan->hasAttribute(obj, Attribute::Translatable))
				continue;
			std::shared_ptr<AttrTranslatable> attr = objMan->getAttribute<AttrTranslatable>(obj, Attribute::Translatable);
			attr->m_x += attr->m_dx * l_dt;
			attr->m_y += attr->m_dy * l_dt;
		}
	}

	void SysTranslator::handleEvent(const ObjectId &l_obj, Event &l_id)
	{

	}

}