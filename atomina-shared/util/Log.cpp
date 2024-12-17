#include "pch.hpp"
#include "Log.hpp"

namespace ATMA
{

    std::shared_ptr<spdlog::logger> Log::s_EngineLogger;

    bool Log::s_initialized = false;

    void Log::Init()
    {
        if(!s_initialized)
        {
            spdlog::set_pattern("%^[%T][thread %t] %n: %v%$");
            s_EngineLogger = spdlog::stdout_color_mt("ATMA");
            s_EngineLogger->set_level(spdlog::level::trace);
            s_initialized = true;
        }
    }

}