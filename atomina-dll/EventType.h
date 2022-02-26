#pragma once
#include "api.h"

namespace ATMA {

	enum class ATMA_API EventType {
		KeyPressed = sf::Event::KeyPressed,
		KeyReleased = sf::Event::KeyReleased,
		MousePressed = sf::Event::MouseButtonPressed,
		MouseReleased = sf::Event::MouseButtonReleased,
		MouseScrolled = sf::Event::MouseWheelScrolled,
		WindowResized = sf::Event::Resized,
		GainedFocus = sf::Event::GainedFocus,
		LostFocus = sf::Event::LostFocus,
		MouseEntered = sf::Event::MouseEntered,
		MouseLeft = sf::Event::MouseLeft,
		Closed = sf::Event::Closed,
		TextEntered = sf::Event::TextEntered,
		Keyboard = sf::Event::Count + 1, Mouse, Joystick,
		GUI_Click, GUI_Release, GUI_Hover, GUI_Leave, GUI_Focus, GUI_Defocus
	};

	enum class ATMA_API EventInfoType {
		RAW,
		GUI
	};

}