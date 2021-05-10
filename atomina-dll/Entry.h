#pragma once
#include "api.h"
#include "Game.h"


//factory function to be implemented by the game 
extern ATMA::Game* ATMA::CreateGame();

/*
* DLL entry point into execution
*/
int main() {
	ATMA::Game* app = ATMA::CreateGame();
	app->run();
	delete app;
}