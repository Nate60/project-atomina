#pragma once
#include "pch.h"
#include "api.h"

namespace ATMA {

	struct ATMA_API EventContext {

		EventContext(const std::string& l_name) : name_(l_name) {}

		std::string name_;
		sf::Vector2i viewSize_, mouse_, wheelDelta_;
		int keyCode_;


		/**
		* Since EventContext will outlive the contents inside it,
		* its contexts will need to be reset once they are handled
		*/
		void clear();

	};

}