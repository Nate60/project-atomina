#include "pch.hpp"
#include "Window.hpp"
#include <SFML/Window/VideoMode.hpp>

namespace ATMA
{

    Window::Window(const std::string &l_name, const sf::Vector2u &l_dimensions)
    {
        m_window.create(sf::VideoMode{l_dimensions}, l_name);
        m_name = l_name;
    }

    Window::Window(const Window &l_other)
    {
        m_window.create(sf::VideoMode{l_other.m_window.getSize()}, l_other.m_name);
        m_name = l_other.m_name;
    }

    Window::~Window() {}

    void Window::beginDraw() {}

    void Window::endDraw() {}

    bool Window::isDone() const
    {
        return m_done;
    }

    bool Window::isFullscreen() const
    {
        return m_fullscreen;
    }

    bool Window::isFocused() const
    {
        return m_focused;
    }

    bool Window::poll(sf::Event &l_e)
    {
        return m_window.pollEvent(l_e);
    }

    void Window::close()
    {
        m_window.close();
    }

    void Window::toggleFullscreen()
    {
        if(m_fullscreen)
        {
            m_fullscreen = false;
        }
        else
        {
            m_fullscreen = true;
        }
    }

    sf::Vector2u Window::getWindowSize()
    {
        return m_window.getSize();
    }

    sf::Rect<float> Window::getViewSpace()
    {
        return m_window.getView().getViewport();
    }

    void Window::clear()
    {
        m_window.clear();
    }

    void Window::display()
    {
        m_window.display();
    }

    void Window::draw(const sf::Drawable &l_drawable, const sf::RenderStates &l_states)
    {
        m_window.draw(l_drawable, l_states);
    }

}