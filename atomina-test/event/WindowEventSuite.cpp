#include "WindowEventSuite.hpp"
#include "event/WindowEvent.hpp"
#include <SFML/Window/Keyboard.hpp>

TEST_F(EventFixture, KeyPressedIsPassedToState)
{
    bool flag{false};
    std::unique_ptr<TestState> state{new TestState{}};
    state->m_onKeyPress = [&flag]() -> void { flag = true; };
    auto id = state->getId();
    this->ctx.addState(id, std::move(state));
    sf::Event e{};
    e.type = sf::Event::KeyPressed;
    e.key.code = sf::Keyboard::W;
    this->ctx.pushWindowEvent(ATMA::WindowEvent(e));
    EXPECT_TRUE(flag);
}

TEST_F(EventFixture, KeyReleasedIsPassedToState)
{
    bool flag{false};
    std::unique_ptr<TestState> state{new TestState{}};
    state->m_onKeyRelease = [&flag]() -> void { flag = true; };
    auto id = state->getId();
    this->ctx.addState(id, std::move(state));
    sf::Event e{};
    e.type = sf::Event::KeyReleased;
    e.key.code = sf::Keyboard::W;
    this->ctx.pushWindowEvent(ATMA::WindowEvent(e));
    EXPECT_TRUE(flag);
}

TEST_F(EventFixture, MousePressedIsPassedToState) 
{
    bool flag{false};
    std::unique_ptr<TestState> state{new TestState{}};
    state->m_onMousePress = [&flag]() -> void { flag = true; };
    auto id = state->getId();
    this->ctx.addState(id, std::move(state));
    sf::Event e{};
    e.type = sf::Event::MouseButtonPressed;
    e.mouseButton.button = sf::Mouse::Button::Left;
    this->ctx.pushWindowEvent(ATMA::WindowEvent(e));
    EXPECT_TRUE(flag);
}

TEST_F(EventFixture, MouseReleasedIsPassedToState) 
{
    bool flag{false};
    std::unique_ptr<TestState> state{new TestState{}};
    state->m_onMouseRelease = [&flag]() -> void { flag = true; };
    auto id = state->getId();
    this->ctx.addState(id, std::move(state));
    sf::Event e{};
    e.type = sf::Event::MouseButtonReleased;
    e.mouseButton.button = sf::Mouse::Button::Left;
    this->ctx.pushWindowEvent(ATMA::WindowEvent(e));
    EXPECT_TRUE(flag);
}

TEST_F(EventFixture, MouseMovedIsPassedToState) 
{
    bool flag{false};
    std::unique_ptr<TestState> state{new TestState{}};
    state->m_onMouseMove = [&flag]() -> void { flag = true; };
    auto id = state->getId();
    this->ctx.addState(id, std::move(state));
    sf::Event e{};
    e.type = sf::Event::MouseMoved;
    e.mouseMove.x = 0;
    e.mouseMove.y = 0;
    this->ctx.pushWindowEvent(ATMA::WindowEvent(e));
    EXPECT_TRUE(flag);
}