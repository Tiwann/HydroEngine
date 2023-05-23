#pragma once
#include "SharedPointer.h"
#include <spdlog/spdlog.h>

#if defined(HYDRO_CORE)
    #if !(defined(HYDRO_LOG_TRACE) && defined(HYDRO_LOG_WARNING) && defined(HYDRO_LOG_ERROR) && defined(HYDRO_LOG_INFO))
        #if defined(HYDRO_DEBUG)
            #define HYDRO_LOG_TRACE(...)    Hydro::Log::GetCoreLogger().trace(__VA_ARGS__)
            #define HYDRO_LOG_INFO(...)     Hydro::Log::GetCoreLogger().info(__VA_ARGS__)
            #define HYDRO_LOG_WARNING(...)  Hydro::Log::GetCoreLogger().warn(__VA_ARGS__)
            #define HYDRO_LOG_ERROR(...)    Hydro::Log::GetCoreLogger().error(__VA_ARGS__)
        #else
            #define HYDRO_LOG_TRACE(...)    HYDRO_NULL_MACRO
            #define HYDRO_LOG_INFO(...)     HYDRO_NULL_MACRO
            #define HYDRO_LOG_WARNING(...)  HYDRO_NULL_MACRO
            #define HYDRO_LOG_ERROR(...)    HYDRO_NULL_MACRO
        #endif
    #endif
#endif

namespace Hydro
{
    class HYDRO_API Log
    {
    public:
        static spdlog::logger& GetCoreLogger();
        static spdlog::logger& GetClientLogger();
        static void Init();
    private:
        static Ref<spdlog::logger> s_CoreLogger;
        static Ref<spdlog::logger> s_ClientLogger;
    };
}
