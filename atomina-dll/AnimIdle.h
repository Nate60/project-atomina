#pragma once
#include "pch.h"
#include "api.h"
#include "AnimBase.h"

namespace ATMA
{

	class ATMA_API AnimIdle: public AnimBase
	{
	public:
		AnimIdle(
			const std::string &l_name,
			const unsigned int &l_width,
			const unsigned int &l_height,
			const unsigned int &l_startFrame = 0,
			const unsigned int &l_endFrame = 0,
			const unsigned int &l_activeStart = 0,
			const unsigned int &l_activeEnd = 0,
			const bool &l_loop = false
		);
		

		AnimIdle(
			const std::string &l_name,
			const sf::Vector2u &l_dimensions,
			const unsigned int &l_startFrame = 0,
			const unsigned int &l_endFrame = 0,
			const unsigned int &l_activeStart = 0,
			const unsigned int &l_activeEnd = 0,
			const bool &l_loop = false
		);

	protected:
		virtual void step() override;
	};

}