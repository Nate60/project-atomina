#pragma once
#include "../pch.hpp"
#include "../core/api.hpp"
#include "AtominaException.hpp"

namespace ATMA
{

    /**
     * static class to interface with spdlog
     * and provide logging functionality macros
     */
    class Log
    {
    public:
        /**
         * Starts the spdlog engine
         */
        static void Init();

        /**
         * gets the singleton engine logger
         * @returns shared pointer of the logger
         */
        inline static std::shared_ptr<spdlog::logger> &GetEngineLogger()
        {
            if(s_initialized)
            {
                return s_EngineLogger;
            }
            else
            {
                throw InitializationException("must call Log.Init() before calling logger");
            }
        }
    private:
        static std::shared_ptr<spdlog::logger> s_EngineLogger;
        static bool s_initialized;
    };

}

#define ATMA_ENGINE_ERROR(...) ::ATMA::Log::GetEngineLogger()->error(__VA_ARGS__)
#define ATMA_ENGINE_WARN(...) ::ATMA::Log::GetEngineLogger()->warn(__VA_ARGS__)
#define ATMA_ENGINE_INFO(...) ::ATMA::Log::GetEngineLogger()->info(__VA_ARGS__)
#define ATMA_ENGINE_TRACE(...) ::ATMA::Log::GetEngineLogger()->trace(__VA_ARGS__)
