#pragma once
#include "api.hpp"
#include "Game.hpp"
#ifdef _WINDOWS
#    include <winsock2.h>
//#    include "platform/Win/os/OSContextWinImpl.hpp"
#endif

namespace ATMA
{

    /**
     * Factory function to be implemented by the game so the engine can
     * call the game loop on the user defined game app
     */
    extern std::unique_ptr<Game> CreateGame();
}
