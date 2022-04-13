#pragma once
#include <functional>
#include <atomina.h>



class GameState: public ATMA::BaseState
{
public:
	GameState(ATMA::StateManager &l_stateMan): BaseState(l_stateMan)
	{

	}

	virtual void onCreate()
	{
		auto &ctx = m_stateMan.getContext();
		ctx.m_event_manager->addCallBack(static_cast<ATMA::EventType>(sf::Event::EventType::KeyPressed), [&](ATMA::Event &e){
			m_stateMan.getContext().m_system_manager->addEvent(static_cast<ATMA::ObjectId>(0u), e);
			}, getId());
		ctx.m_event_manager->addCallBack(static_cast<ATMA::EventType>(sf::Event::EventType::KeyReleased), [&](ATMA::Event &e){
			m_stateMan.getContext().m_system_manager->addEvent(static_cast<ATMA::ObjectId>(0u), e);
			}, getId());
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
		return static_cast<ATMA::StateType>(ATMA::State::COUNT);
	}

	virtual void update(const sf::Time &l_time)
	{

	}
	virtual void draw()
	{

	}

};