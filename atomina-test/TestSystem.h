#pragma once
#include "CppUnitTest.h"
#include <functional>
#include <atomina.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

class TestSystem: public ATMA::SysBase
{
public:
	TestSystem(const ATMA::SystemType &l_type, ATMA::SystemManager &l_man) : SysBase(l_type,l_man)
	{
		std::bitset<ATConst::OBJECT_BIT_SIZE> bits;
		bits.set((int)ATMA::Attribute::Translatable);
		m_req = bits;
	}

	~TestSystem()
	{

	}

	void notify(const ATMA::Message &l_message)
	{

	}

	void update(float l_dt) override
	{

	}

	void handleEvent(const ATMA::ObjectId &l_obj, ATMA::Event &l_id) override
	{
		auto &obj_man = m_sysMan.getObjectManager();
		Assert::IsTrue(obj_man->hasAttribute(l_obj, ATMA::Attribute::Translatable));
		auto &obj_attr = obj_man->getAttribute<ATMA::AttrTranslatable>(l_obj, ATMA::Attribute::Translatable);
		obj_attr->m_x++;
	}

};