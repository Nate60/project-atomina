#include "../pch.hpp"
#include "Entry.hpp"

/*
* DLL entry point into execution
*/
int main() {
	
	ATMA::Log::Init();
	ATMA_ENGINE_INFO("Init logger!");
	std::unique_ptr<ATMA::Game> app = ATMA::CreateGame();
	try
	{
		app->run();
	}
	catch(std::exception e)
	{
		ATMA_ENGINE_ERROR("Fatal error {0} shutting down...", e.what());
	}

	app->shutdown();
}