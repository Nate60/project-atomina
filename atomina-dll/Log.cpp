#include "Log.h"

namespace ATMA {

	std::shared_ptr<spdlog::logger> Log::EngineLogger_s;

	bool Log::initialized = false;

	void Log::Init() {
		if (!initialized) {
			spdlog::set_pattern("%^[%T] %n: %v%$");
			EngineLogger_s = spdlog::stdout_color_mt("ATMA");
			EngineLogger_s->set_level(spdlog::level::trace);
			initialized = true;
		}
	}

}