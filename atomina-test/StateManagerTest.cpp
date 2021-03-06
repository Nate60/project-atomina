#include "CppUnitTest.h"
#include <atomina.h>
#include <string>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace State
{

	TEST_CLASS(State_Manager)
	{
		ATMA::StateManager sm{};

		TEST_METHOD_INITIALIZE(Add_Attr_and_Sys_types)
		{
			sm.purge();
		}


		TEST_METHOD(Register_State)
		{
			sm.registerState<ATMA::DummyState>(ATMA::State::Dummy);
			Assert::IsTrue(sm.hasState(ATMA::State::Dummy));
		}

		TEST_METHOD(Remove_State)
		{
			sm.registerState<ATMA::DummyState>(ATMA::State::Dummy);
			Assert::IsTrue(sm.hasState(ATMA::State::Dummy));
			sm.remove(ATMA::State::Dummy);
			Assert::IsFalse(sm.hasState(ATMA::State::Dummy));
		}

		TEST_METHOD(Purge_States)
		{
			sm.registerState<ATMA::DummyState>(ATMA::State::Dummy);
			Assert::IsTrue(sm.hasState(ATMA::State::Dummy));
			sm.purge();
			Assert::IsFalse(sm.hasState(ATMA::State::Dummy));
		}



	};

}