#include "pch.h"
#include "EventContext.h"

namespace ATMA {

	void EventContext::clear() {
		name_ = "";
		keyCode_ = -1;
		viewSize_ = sf::Vector2i(0, 0);
		mouse_ = sf::Vector2i(0, 0);
		wheelDelta_ = sf::Vector2i(0, 0);
	}

}