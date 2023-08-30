#pragma once
#include "SharedPointer.h"
#include "Macros.h"
#include <spdlog/spdlog.h>

#if defined(HYDRO_CORE)
    #if !defined(HYDRO_LOG)
        #if defined(HYDRO_DEBUG)
            #define HYDRO_LOG(CategoryName, InVerbosity, ...) \
                Hydro::Log::SetCurrentCategoryName(CategoryName##LogCategory##::s_CategoryName);\
                switch (InVerbosity) { \
                case Verbosity::Trace:      Hydro::Log::GetCoreLogger().trace(__VA_ARGS__); break; \
                case Verbosity::Info:       Hydro::Log::GetCoreLogger().info(__VA_ARGS__); break; \
                case Verbosity::Warning:    Hydro::Log::GetCoreLogger().warn(__VA_ARGS__); break; \
                case Verbosity::Error:      Hydro::Log::GetCoreLogger().error(__VA_ARGS__); break; \
                }((void)0)
        #else
            #define HYDRO_LOG(CategoryName, Verbosity, ...)    HYDRO_NULL_MACRO
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
        static void SetCurrentCategoryName(std::string CategoryName);
        friend class LogCategoryFormatter;
    private:
        static std::string s_CurrentCategoryName;
        static Ref<spdlog::logger> s_CoreLogger;
        static Ref<spdlog::logger> s_ClientLogger;
    };

    
}
