#pragma once
#include "../pch.hpp"
#include "../core/api.hpp"

namespace ATConst {

	static const sf::Image &getDefaultImage()
	{
		static sf::Image img; 
		static const sf::Uint8 pixels[16]{0xFF,0x00,0xFF,0xFF,
		0x00,0x00,0x00,0xFF,
		0xFF,0x00,0xFF,0xFF,
		0x00,0x00,0x00,0xFF};
		img.create({2u,2u},pixels);
		return img;
	}

	static const size_t OBJECT_BIT_SIZE = 32;


}
