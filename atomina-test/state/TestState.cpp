#include "TestState.hpp"
#include "OAS/System.hpp"
#include "util/Log.hpp"

TestState::TestState(): ATMA::BaseState() {}

TestState::~TestState() {}

void
TestState::onCreate()
{
}

void
TestState::onDestroy()
{
}

void
TestState::activate()
{
    if(ctx.hasSystem(0u))
        ctx.enableSystem(0u);
}

void
TestState::deactivate()
{
    if(ctx.hasSystem(0u))
        ctx.disableSystem(0u);
}

void
TestState::handleEvent(const ATMA::WindowEvent &l_e)
{
    ATMA_ENGINE_INFO("TestState handling Window Event of Type: {0:d}", int(l_e.m_event.type));
    if(l_e.m_event.type == sf::Event::KeyPressed)
    {
        m_onKeyPress();
    }
    else if(l_e.m_event.type == sf::Event::KeyReleased)
    {
        m_onKeyRelease();
    }
    else if(l_e.m_event.type == sf::Event::MouseButtonPressed)
    {
        m_onMousePress();
    }
    else if(l_e.m_event.type == sf::Event::MouseButtonReleased)
    {
        m_onMouseRelease();
    }
    else if(l_e.m_event.type == sf::Event::MouseMoved)
    {
        m_onMouseMove();
    }
    else
    {
        ATMA_ENGINE_INFO("TestState window event went unhandled");
    }
}

void
TestState::update(const sf::Time &l_time)
{
}

void
TestState::draw()
{
}