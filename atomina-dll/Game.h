#pragma once
#include "api.h"

namespace ATMA {

	class ATMA_API Game
	{
	public:
		Game();
		virtual ~Game();
		virtual void run();
		virtual void shutdown();

		bool active = false;

	};

	std::unique_ptr<Game> CreateGame();
	





}

