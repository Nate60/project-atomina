#pragma once
#include "../pch.hpp"
#include "../core/api.hpp"
#include "AtominaException.hpp"

namespace ATMA
{

    class ATMA_API Log
    {
    public:
        static void Init();

        inline static std::shared_ptr<spdlog::logger> &GetEngineLogger()
        {
            if(s_initialized)
            {
                return s_EngineLogger;
            }
            else
            {
                throw LoggerNotInitializedException("must call Log.Init() before calling logger");
            }
        }
    private:
        static std::shared_ptr<spdlog::logger> s_EngineLogger;
        static bool s_initialized;
    };

}

#define ATMA_ENGINE_ERROR(...) ::ATMA::Log::GetEngineLogger()->error(__VA_ARGS__)
#define ATMA_ENGINE_WARN(...)  ::ATMA::Log::GetEngineLogger()->warn(__VA_ARGS__)
#define ATMA_ENGINE_INFO(...)  ::ATMA::Log::GetEngineLogger()->info(__VA_ARGS__)
#define ATMA_ENGINE_TRACE(...) ::ATMA::Log::GetEngineLogger()->trace(__VA_ARGS__)
