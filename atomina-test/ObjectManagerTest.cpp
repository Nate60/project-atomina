#include "CppUnitTest.h"
#include <functional>
#include <atomina.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OAS {

	TEST_CLASS(Object_Manager) {

		ATMA::ObjectManager objMan;

		TEST_CLASS_INITIALIZE(Start_Logger) {
			ATMA::Log::Init();
		}

		TEST_METHOD_INITIALIZE(Add_Attr_types) {
			objMan.addAttributeType<ATMA::AttrTranslatable>(ATMA::Attribute::Translatable);
		}

		TEST_METHOD_CLEANUP(Purge_Object_Manager) {
			objMan.purge();
		}

		TEST_METHOD(Two_objects_have_unique_ids) {
			unsigned int objID = objMan.createObject(std::bitset<ATConst::OBJECT_BIT_SIZE>()).value_or(100u);
			unsigned int objID2 = objMan.createObject(std::bitset<ATConst::OBJECT_BIT_SIZE>()).value_or(100u);
			Assert::AreNotEqual(objID, objID2);

		}

		TEST_METHOD(Add_Attr_Type) {

			unsigned int objID = objMan.createObject(std::bitset<ATConst::OBJECT_BIT_SIZE>()).value_or(100u);
			Assert::IsTrue(objMan.addAttribute(objID, ATMA::Attribute::Translatable));

		}

		TEST_METHOD(Add_same_Attr) {
			unsigned int objID = objMan.createObject(std::bitset<ATConst::OBJECT_BIT_SIZE>()).value_or(100u);
			objMan.addAttribute(objID, ATMA::Attribute::Translatable);
			Assert::IsFalse(objMan.addAttribute(objID, ATMA::Attribute::Translatable));

		}

		TEST_METHOD(Add_Attr_None) {
			unsigned int objID = objMan.createObject(std::bitset<ATConst::OBJECT_BIT_SIZE>()).value_or(100u);
			Assert::IsFalse(objMan.addAttribute(objID, ATMA::Attribute::None));

		}


		TEST_METHOD(Add_non_existent_object) {
			Assert::IsFalse(objMan.addAttribute(1, ATMA::Attribute::Translatable));

		}
		TEST_METHOD(Remove_Attr) {
			unsigned int objID = objMan.createObject(std::bitset<ATConst::OBJECT_BIT_SIZE>()).value_or(100u);
			objMan.addAttribute(objID, ATMA::Attribute::Translatable);
			Assert::IsTrue(objMan.removeAttribute(objID, ATMA::Attribute::Translatable));

		}

		TEST_METHOD(Remove_same_Attr) {
			unsigned int objID = objMan.createObject(std::bitset<ATConst::OBJECT_BIT_SIZE>()).value_or(100u);
			objMan.addAttribute(objID, ATMA::Attribute::Translatable);
			objMan.removeAttribute(objID, ATMA::Attribute::Translatable);
			Assert::IsFalse(objMan.removeAttribute(objID, ATMA::Attribute::Translatable));

		}
		TEST_METHOD(Remove_object) {
			unsigned int objID = objMan.createObject(std::bitset<ATConst::OBJECT_BIT_SIZE>()).value_or(100u);
			objMan.addAttribute(objID, ATMA::Attribute::Translatable);
			Assert::IsTrue(objMan.removeObject(objID));
		}

		TEST_METHOD(Remove_non_existent_object) {
			Assert::IsFalse(objMan.removeObject(1));
		}

		TEST_METHOD(Remove_non_existent_object_Attr) {
			Assert::IsFalse(objMan.removeAttribute(1, ATMA::Attribute::Translatable));
		}

		TEST_METHOD(Get_Attr) {
			unsigned int objID = objMan.createObject(std::bitset<ATConst::OBJECT_BIT_SIZE>()).value_or(100u);
			objMan.addAttribute(objID, ATMA::Attribute::Translatable);
			Assert::IsTrue(objMan.getAttribute<ATMA::AttrTranslatable>(objID, ATMA::Attribute::Translatable)->m_x == 0);
		}


		TEST_METHOD(Get_non_existent_object) {
			try
			{
				auto func = []()
				{
					ATMA::ObjectManager objMan;
					objMan.getAttribute<ATMA::AttrBase>(1, ATMA::Attribute::None)->getType();
				};
				Assert::ExpectException<std::domain_error>(func);
			}
			catch(...)
			{

			}

		}



	};

}