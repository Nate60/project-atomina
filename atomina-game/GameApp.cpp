#include "GameApp.h"

GameApp::GameApp() {

}

GameApp::~GameApp() {

}

ATMA::Game* ATMA::CreateGame() {
	return new GameApp();
}