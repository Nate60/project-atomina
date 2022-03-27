#pragma once
#include "CppUnitTest.h"
#include <functional>
#include <atomina.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


class TestState: public ATMA::BaseState
{
public:
	TestState(ATMA::StateManager &l_stateMan): BaseState(l_stateMan)
	{

	}

	virtual void onCreate()
	{
		auto &ctx = m_stateMan.getContext();
		ctx.m_event_manager->addCallBack<int>(static_cast<ATMA::EventType>(100u), [](ATMA::Event &e){
			Assert::IsTrue(e.m_type > 0);
			});
		ctx.m_event_manager->addCallBack<int>(static_cast<ATMA::EventType>(101u), [&](ATMA::Event &e){
			m_stateMan.getContext().m_system_manager->addEvent(static_cast<ATMA::ObjectId>(0u), e);
			m_stateMan.getContext().m_system_manager->handleEvents();
			});

	}
	virtual void onDestroy()
	{

	}
	virtual void activate()
	{

	}
	virtual void deactivate()
	{

	}

	virtual ATMA::StateType getId() const override
	{
		return static_cast<ATMA::StateType>(2u);
	}

	virtual void update(const sf::Time &l_time)
	{

	}
	virtual void draw()
	{

	}

};