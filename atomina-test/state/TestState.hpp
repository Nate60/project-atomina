#pragma once
#include "AtominaTest.hpp"
#include "StateFixtures.hpp"
#include "event/WindowEvent.hpp"

class TestState: public ATMA::BaseState
{
public:
    std::function<void()> m_onKeyPress = []() -> void {};
    std::function<void()> m_onKeyRelease = []() -> void {};
    std::function<void()> m_onMousePress = []() -> void {};
    std::function<void()> m_onMouseRelease = []() -> void {};
    std::function<void()> m_onMouseMove = []() -> void {};

    ATMA::ATMAContext &ctx = ATMA::ATMAContext::getContext();

    TestState();

    virtual ~TestState();

    virtual void onCreate() override;
    virtual void onDestroy() override;
    virtual void activate() override;
    virtual void deactivate() override;

    virtual void handleEvent(const ATMA::WindowEvent &l_e) override;

    virtual unsigned int getId() const override
    {
        return 3u;
    }

    virtual void update(const sf::Time &l_time) override;
    virtual void draw() override;
};