#include "CppUnitTest.h"
#include <functional>
#include <atomina.h>
#include "TestState.h"
#include "TestSystem.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace EventTesting
{

	TEST_CLASS(Event_Manager)
	{


		TEST_CLASS_INITIALIZE(Start_Logger)
		{
			ATMA::Log::Init();
		}

		TEST_METHOD(Add_event_callback)
		{
			ATMA::EventManager em{};
			auto callback = [](ATMA::Event &e){
				Assert::IsTrue(e.m_type > 0);
			};
			Assert::IsTrue(em.addCallBack(static_cast<ATMA::EventType>(100u), callback));
		}

		TEST_METHOD(Add_event_for_existing_callback)
		{
			ATMA::EventManager em{};
			auto callback = [](ATMA::Event &e){
				Assert::IsTrue(e.m_type > 0);
			};
			em.addCallBack(static_cast<ATMA::EventType>(100u), callback);
			Assert::IsFalse(em.addCallBack(static_cast<ATMA::EventType>(100u), callback));
		}

		TEST_METHOD(Remove_event_callback)
		{
			ATMA::EventManager em{};
			auto callback = [](ATMA::Event &e){
				Assert::IsTrue(e.m_type > 0);
			};
			em.addCallBack(static_cast<ATMA::EventType>(100u), callback);
			Assert::IsTrue(em.removeCallBack(static_cast<ATMA::EventType>(100u)));
		}

		TEST_METHOD(Remove_nonexistent_callback)
		{
			ATMA::EventManager em{};
			Assert::IsFalse(em.removeCallBack(static_cast<ATMA::EventType>(100u)));
		}

		TEST_METHOD(Event_invokes_callback)
		{
			ATMA::EventManager em{};
			auto callback = [](ATMA::Event &e){
				Assert::IsTrue(e.m_type > 0);
			};
			em.addCallBack(static_cast<ATMA::EventType>(100u), callback);
			ATMA::Event e{100u, "foo"};
			em.handleEvent(e);
		}

		TEST_METHOD(Event_invokes_state_callback)
		{
			ATMA::ATMAContext ctx{};
			ctx.m_event_manager = std::shared_ptr<ATMA::EventManager>{new ATMA::EventManager{}};
			ATMA::StateManager stateMan{ctx};
			TestState testState{stateMan};
			stateMan.registerState<TestState>(2u);
			ATMA::Event e{100u, "foo"};
			ctx.m_event_manager->handleEvent(e);
		}

		TEST_METHOD(Event_callback_modifies_entity)
		{
			try
			{
				ATMA::ATMAContext ctx{};
				ctx.m_event_manager = std::shared_ptr<ATMA::EventManager>{new ATMA::EventManager{}};
				ctx.m_system_manager = std::shared_ptr<ATMA::SystemManager>{new ATMA::SystemManager{}};

				Assert::IsTrue(ctx.m_system_manager->addSystem<TestSystem>(ATMA::System::Translator));


				auto &objMan = ctx.m_system_manager->getObjectManager();
				auto objId = objMan->createObject();
				objMan->addAttributeType<ATMA::AttrTranslatable>(ATMA::Attribute::Translatable);
				Assert::IsTrue(objMan->addAttribute(objId, ATMA::Attribute::Translatable));
				std::bitset<ATConst::OBJECT_BIT_SIZE> bits = std::bitset<ATConst::OBJECT_BIT_SIZE>();
				bits.set((int)ATMA::Attribute::Translatable);

				ctx.m_system_manager->objectModified(objId, bits);

				ATMA::StateManager stateMan{ctx};
				TestState testState{stateMan};

				Assert::IsTrue(stateMan.registerState<TestState>(2u));
				ATMA::Event e{101u, "foo"};
				ctx.m_event_manager->handleEvent(e);
				auto &obj_attr = objMan->getAttribute<ATMA::AttrTranslatable>(objId, ATMA::Attribute::Translatable);
				Assert::IsTrue(obj_attr->m_x > 0);
			}
			catch(std::exception e)
			{
				Logger::WriteMessage(e.what());
			}
		}

		TEST_METHOD(Event_without_callback_throws)
		{
			try
			{
				Assert::ExpectException<ATMA::ValueNotFoundException>([]()
					{
						ATMA::ATMAContext ctx{};
						ctx.m_event_manager = std::shared_ptr<ATMA::EventManager>{new ATMA::EventManager{}};
						ctx.m_system_manager = std::shared_ptr<ATMA::SystemManager>{new ATMA::SystemManager{}};
						ATMA::Event e{101u, "foo"};
						ctx.m_event_manager->handleEvent(e);
					});
			}
			catch(...)
			{
				 
			}


		}

	};

}