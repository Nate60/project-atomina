#pragma once
#include "pch.h"
#include "api.h"

namespace ATMA {

	struct ATMA_API EventContext {

		EventContext(const std::string& l_name) : m_name(l_name) {}

		std::string m_name;
		sf::Vector2i m_viewSize, m_mouse, m_wheelDelta;
		int m_keyCode;


		/**
		* Since EventContext will outlive the contents inside it,
		* its contexts will need to be reset once they are handled
		*/
		void clear();

	};

}