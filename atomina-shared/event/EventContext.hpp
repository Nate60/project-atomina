#pragma once
#include "../pch.hpp"
#include "../core/api.hpp"

namespace ATMA {

	struct ATMA_API EventContext {

		EventContext(const std::string& l_name) : m_name(l_name), m_keyCode(std::nullopt)
		{}

		std::string m_name;
		sf::Vector2i m_viewSize, m_mouse, m_wheelDelta;
		std::optional<int> m_keyCode;



	};

}