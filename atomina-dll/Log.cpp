#include "Log.h"

namespace ATMA {

	std::shared_ptr<spdlog::logger> Log::EngineLogger_s;

	void Log::Init() {

		spdlog::set_pattern("%^[%T] %n: %v%$");
		EngineLogger_s = spdlog::stdout_color_mt("ATMA");
		EngineLogger_s->set_level(spdlog::level::trace);
	}

}