#pragma once
#include "api.hpp"
#include "Game.hpp"

namespace ATMA
{

#ifdef _WINDOWS
    /**
     * Due to restrictions of MSVC with Compiler unable to implment main
     * within the shared library this function needs to be implmented for the windows platform
     */
    ATMA_API void startGame(std::unique_ptr<Game> l_game);
#else
    /**
     * Factory function to be implemented by the game so the engine can
     * call the game loop on the user defined game app
     */
    extern ATMA_API std::unique_ptr<Game> CreateGame();
#endif
}
