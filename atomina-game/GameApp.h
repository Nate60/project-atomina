#pragma once
#include <atomina.h>
#include "GameState.h"

/*
* extension of the Game class from atomina-api
* used as actual implementation
*/
class GameApp : public ATMA::Game
{
public:

	GameApp();
	~GameApp();
	virtual void run() override;
	virtual void shutdown() override;

};

