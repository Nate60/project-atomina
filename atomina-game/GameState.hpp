#pragma once
#include <functional>
#include <atomina.hpp>

class GameState: public ATMA::BaseState
{
public:
    ATMA::ATMAContext &ctx = ATMA::ATMAContext::getContext();

    GameState(): BaseState() {}

    virtual void onCreate() override {}

    virtual void onDestroy() override {}

    virtual void activate() override {}

    virtual void deactivate() override {}

    virtual unsigned int getId() const override
    {
        return ATMA::StateType(ATMA::State::COUNT);
    }

    virtual void handleEvent(const ATMA::WindowEvent &l_e) override
    {
        sf::Event e = l_e.m_event;
        if(e.type == sf::Event::Closed)
        {
            ctx.dispatchObjectEvent(ATMA::ObjectEventContext{
                ATMA::ObjectEventType(ATMA::ObjectEvent::ShutDown)});
        }
    }

    virtual void update(const sf::Time &l_time) override {}

    virtual void draw() override {}
};