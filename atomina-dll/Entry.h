#pragma once
#include "api.h"
#include "Game.h"

//Unit Test Project does not behave well with main functions
#ifndef TEST_PROJECT

//factory function to be implemented by the game 
extern std::unique_ptr<ATMA::Game> ATMA::CreateGame();

/*
* DLL entry point into execution
*/
int main() {
	
	ATMA::Log::Init();
	ATMA_ENGINE_WARN("Init logger!");
	std::unique_ptr<ATMA::Game> app = ATMA::CreateGame();
	app->run();
	app->shutdown();
}

#endif