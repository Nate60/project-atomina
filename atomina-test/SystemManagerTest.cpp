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
			try
			{
				auto id = objMan.createObject(std::bitset<ATConst::OBJECT_BIT_SIZE>()).value_or(100u);
				std::bitset<ATConst::OBJECT_BIT_SIZE> bits = std::bitset<ATConst::OBJECT_BIT_SIZE>();
				bits.set((int)ATMA::Attribute::Translatable);
				objMan.addAttribute(id, ATMA::Attribute::Translatable);
				sysMan.objectModified(id, bits);
				std::shared_ptr<ATMA::SysTranslator> sys = sysMan.getSystem<ATMA::SysTranslator>(ATMA::System::Translator);
				Assert::IsTrue(sys->hasObject(id));
			}
			catch(std::exception e)
			{
				std::cout << "failed: " << e.what() << std::endl;
			}

		}


		TEST_METHOD(Removing_object) {
			auto id = objMan.createObject(std::bitset<ATConst::OBJECT_BIT_SIZE>()).value();
			std::bitset<ATConst::OBJECT_BIT_SIZE> bits = std::bitset<ATConst::OBJECT_BIT_SIZE>();
			bits.set((int)ATMA::Attribute::Translatable);
			objMan.addAttribute(id, ATMA::Attribute::Translatable);
			sysMan.objectModified(id, bits);
			sysMan.removeObject(id);
			std::shared_ptr<ATMA::SysTranslator> sys = sysMan.getSystem<ATMA::SysTranslator>(ATMA::System::Translator);
			Assert::IsFalse(sys->hasObject(id));
		}



	};

}