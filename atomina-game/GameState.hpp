#pragma once
#include <functional>
#include <atomina.hpp>

class GameState: public ATMA::BaseState
{
public:
    GameState(): BaseState() {}

    virtual void onCreate() override
    {
        // auto &ctx = m_stateMan.getContext();
        // ctx.m_event_manager->addCallBack(static_cast<ATMA::EventType>(sf::Event::EventType::KeyPressed),
        // [&](ATMA::Event &e){
        // 	m_stateMan.getContext().m_system_manager->addEvent(static_cast<ATMA::ObjectId>(0u), e);
        // 	}, getId());
        // ctx.m_event_manager->addCallBack(static_cast<ATMA::EventType>(sf::Event::EventType::KeyReleased),
        // [&](ATMA::Event &e){
        // 	m_stateMan.getContext().m_system_manager->addEvent(static_cast<ATMA::ObjectId>(0u), e);
        // 	}, getId());
    }

    virtual void onDestroy() override {}

    virtual void activate() override {}

    virtual void deactivate() override {}

    virtual unsigned int getId() const override
    {
        return ATMA::StateType(ATMA::State::COUNT);
    }

    virtual void update(const sf::Time &l_time) override {}

    virtual void draw() override {}
};