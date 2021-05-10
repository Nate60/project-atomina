#include <atomina.h>
/*
* Classes, members, or functions that are expected to be defined by the dll so that the test solution may compile
*/

/*
* Atomina-API expects that there be an extension of the Game class and that there be a factory function for it as well
*/
class GameApp : public ATMA::Game
{
public:

	GameApp() {

	}

	~GameApp() {

	}

};

ATMA::Game* ATMA::CreateGame() {
	return new GameApp();
}