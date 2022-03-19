
#include "GameApp.h"

GameApp::GameApp() {

}

GameApp::~GameApp() {

}

std::unique_ptr<ATMA::Game> ATMA::CreateGame() {
	return std::unique_ptr<ATMA::Game>{new GameApp()};
}