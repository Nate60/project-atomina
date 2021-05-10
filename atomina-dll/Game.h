#pragma once
#include "api.h"

namespace ATMA {

	/*
	* Abstract class used as an entry point for the game
	*/

	class ATMA_API Game
	{
	public:
		Game();
		virtual ~Game();
		void run();


		bool active = false;

	};

	Game* CreateGame();

}

