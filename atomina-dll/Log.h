#pragma once
#include "api.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace ATMA {
	
	class ATMA_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetEngineLogger() { return EngineLogger_s; }

	private: 
		
		static std::shared_ptr<spdlog::logger> EngineLogger_s;
		static bool initialized;
	};

}

#define ATMA_ENGINE_ERROR(...) ::ATMA::Log::GetEngineLogger()->error(__VA_ARGS__)
#define ATMA_ENGINE_WARN(...)  ::ATMA::Log::GetEngineLogger()->warn(__VA_ARGS__)
#define ATMA_ENGINE_INFO(...)  ::ATMA::Log::GetEngineLogger()->info(__VA_ARGS__)
#define ATMA_ENGINE_TRACE(...) ::ATMA::Log::GetEngineLogger()->trace(__VA_ARGS__)