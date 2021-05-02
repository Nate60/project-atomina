#include "GameApp.h"

GameApp::GameApp() {

}

GameApp::~GameApp() {

}

int main() {
	GameApp* app = new GameApp();
	app->run();
	delete app;
}