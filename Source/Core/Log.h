#pragma once
#include "SharedPointer.h"
#include <spdlog/logger.h>
#include "Macros.h"
#include <string>

#if defined(HYDRO_CORE)
    #if defined(HYDRO_DEBUG)
        #define HYDRO_LOG(CategoryName, InVerbosity, ...) \
        Hydro::Log::SetCurrentCategoryName(CategoryName##LogCategory::s_CategoryName);\
        switch (InVerbosity) { \
        case Hydro::Verbosity::Trace:      Hydro::Log::GetCoreLogger().trace(__VA_ARGS__); break; \
        case Hydro::Verbosity::Info:       Hydro::Log::GetCoreLogger().info(__VA_ARGS__); break; \
        case Hydro::Verbosity::Warning:    Hydro::Log::GetCoreLogger().warn(__VA_ARGS__); break; \
        case Hydro::Verbosity::Error:      Hydro::Log::GetCoreLogger().error(__VA_ARGS__); break; \
        }((void)0)
    #else
        #define HYDRO_LOG(CategoryName, Verbosity, ...) HYDRO_VOID
    #endif
#else
    #if defined(HYDRO_DEBUG)
        #define HYDRO_LOG(CategoryName, InVerbosity, ...) \
        Hydro::Log::SetCurrentCategoryName(CategoryName##LogCategory::s_CategoryName);\
        switch (InVerbosity) { \
        case Hydro::Verbosity::Trace:      Hydro::Log::GetClientLogger().trace(__VA_ARGS__); break; \
        case Hydro::Verbosity::Info:       Hydro::Log::GetClientLogger().info(__VA_ARGS__); break; \
        case Hydro::Verbosity::Warning:    Hydro::Log::GetClientLogger().warn(__VA_ARGS__); break; \
        case Hydro::Verbosity::Error:      Hydro::Log::GetClientLogger().error(__VA_ARGS__); break; \
        }((void)0)
    #else
        #define HYDRO_LOG(CategoryName, Verbosity, ...)    HYDRO_VOID
    #endif
#endif

namespace Hydro
{
    class Log
    {
    public:
        static spdlog::logger& GetCoreLogger();
        static spdlog::logger& GetClientLogger();
        static void Init();
        static void SetCurrentCategoryName(std::string CategoryName);
        friend class LogCategoryFormatter;
    private:
        static std::string s_CurrentCategoryName;
        static Ref<spdlog::logger> s_CoreLogger;
        static Ref<spdlog::logger> s_ClientLogger;
    };
    
    
}
