#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

namespace ATMA
{

    struct ATMA_API EventContext
    {

        EventContext():
            m_sfEvent(std::nullopt),
            m_viewSize(std::nullopt),
            m_mouse(std::nullopt),
            m_wheelDelta(std::nullopt),
            m_keyCode(std::nullopt)
        {
        }

        EventContext(
            std::optional<sf::Event> l_sfEvent,
            std::optional<sf::Vector2i> l_viewSize = std::nullopt,
            std::optional<sf::Vector2i> l_mouse = std::nullopt,
            std::optional<sf::Vector2i> l_wheelDelta = std::nullopt,
            std::optional<int> l_keyCode = std::nullopt
        ):
            m_sfEvent(l_sfEvent),
            m_viewSize(l_viewSize),
            m_mouse(l_mouse),
            m_wheelDelta(l_wheelDelta),
            m_keyCode(l_keyCode)
        {
        }

        const std::optional<sf::Event> m_sfEvent;
        const std::optional<sf::Vector2i> m_viewSize, m_mouse, m_wheelDelta;
        const std::optional<int> m_keyCode;
    };

}