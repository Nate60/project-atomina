#include "pch.h"
#include "EventContext.h"

namespace ATMA {

	void EventContext::clear() {
		m_name = "";
		m_keyCode = -1;
		m_viewSize = sf::Vector2i(0, 0);
		m_mouse = sf::Vector2i(0, 0);
		m_wheelDelta = sf::Vector2i(0, 0);
	}

}