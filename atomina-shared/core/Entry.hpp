#pragma once
#include "api.hpp"
#include "Game.hpp"

namespace ATMA
{

#ifdef _WINDOWS	
	ATMA_API void startGame(std::unique_ptr<Game> l_game);
#else
	extern ATMA_API std::unique_ptr<Game> CreateGame();
#endif
}

