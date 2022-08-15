#pragma once
#include "api.hpp"
#include "Game.hpp"

// factory function to be implemented by the game
extern std::unique_ptr<ATMA::Game> ATMA::CreateGame();
