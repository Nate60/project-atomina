#include "CppUnitTest.h"
#include <functional>
#include <atomina.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OAS {

	TEST_CLASS(System_Manager) {

		ATMA::ObjectManager objMan;
		ATMA::SystemManager sysMan;

		TEST_CLASS_INITIALIZE(Start_Logger) {
			ATMA::Log::Init();
		}

		TEST_METHOD_INITIALIZE(Add_Attr_and_Sys_types) {
			objMan.addAttributeType<ATMA::AttrTranslatable>(ATMA::Attribute::Translatable);
			sysMan.addSystem<ATMA::SysTranslator>(ATMA::System::Translator);
		}

		TEST_METHOD_CLEANUP(Purge_Managers) {
			objMan.purge();
			sysMan.purgeObjects();
			sysMan.purgeSystems();
		}

		TEST_METHOD(Modified_object_moves_systems) {

			auto id = objMan.createObject(std::bitset<ATConst::OBJECT_BIT_SIZE>());
			std::bitset<ATConst::OBJECT_BIT_SIZE> bits = std::bitset<ATConst::OBJECT_BIT_SIZE>();
			bits.set((int)ATMA::Attribute::Translatable);
			objMan.addAttribute(id, ATMA::Attribute::Translatable);
			sysMan.objectModified(id, bits);
			std::shared_ptr<ATMA::SysTranslator> sys = sysMan.getSystem<ATMA::SysTranslator>(ATMA::System::Translator);
			Assert::IsTrue(sys->hasObject(id));

		}


		TEST_METHOD(Removing_object) {
			auto id = objMan.createObject(std::bitset<ATConst::OBJECT_BIT_SIZE>());
			std::bitset<ATConst::OBJECT_BIT_SIZE> bits = std::bitset<ATConst::OBJECT_BIT_SIZE>();
			bits.set((int)ATMA::Attribute::Translatable);
			objMan.addAttribute(id, ATMA::Attribute::Translatable);
			sysMan.objectModified(id, bits);
			sysMan.removeObject(id);
			std::shared_ptr<ATMA::SysTranslator> sys = sysMan.getSystem<ATMA::SysTranslator>(ATMA::System::Translator);
			Assert::IsFalse(sys->hasObject(id));
		}

		TEST_METHOD(get_system)
		{
			sysMan.addSystem<ATMA::SysTranslator>(ATMA::System::Translator);
			auto sys = sysMan.getSystem<ATMA::SysTranslator>(ATMA::System::Translator);
			Assert::IsTrue(sys->getType() == 1u);
		}

		TEST_METHOD(add_existing_system)
		{
			Assert::IsFalse(sysMan.addSystem<ATMA::SysTranslator>(ATMA::System::Translator));
		}

		TEST_METHOD(get_nonexistent_system)
		{
			try
			{
				sysMan.purgeSystems();
				auto func = [=](){ sysMan.getSystem<ATMA::SysTranslator>(ATMA::System::Translator); };
				Assert::ExpectException<ATMA::ValueNotFoundException>(func);
			}
			catch(...)
			{

			}
		}

		TEST_METHOD(add_non_subclass_system)
		{
			try
			{
				auto func = [=](){ sysMan.addSystem<ATMA::AtominaException>(ATMA::System::Translator); };
				Assert::ExpectException<std::bad_cast>(func);
			}
			catch(...)
			{

			}
		}

		TEST_METHOD(purge_systems)
		{
			try
			{
				sysMan.purgeSystems();
				auto func = [=](){ sysMan.getSystem<ATMA::SysTranslator>(ATMA::System::Translator); };
				Assert::ExpectException<ATMA::ValueNotFoundException>(func);
			}
			catch(...)
			{

			}


		}

		TEST_METHOD(purge_objects)
		{
			auto id = objMan.createObject(std::bitset<ATConst::OBJECT_BIT_SIZE>());
			std::bitset<ATConst::OBJECT_BIT_SIZE> bits = std::bitset<ATConst::OBJECT_BIT_SIZE>();
			bits.set((int)ATMA::Attribute::Translatable);
			objMan.addAttribute(id, ATMA::Attribute::Translatable);
			sysMan.objectModified(id, bits);
			sysMan.purgeObjects();
			std::shared_ptr<ATMA::SysTranslator> sys = sysMan.getSystem<ATMA::SysTranslator>(ATMA::System::Translator);
			Assert::IsFalse(sys->hasObject(id));
		}


	};

}