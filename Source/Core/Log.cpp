#include "HydroPCH.h"
#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Hydro
{
    Ref<spdlog::logger> Log::s_CoreLogger = spdlog::stdout_color_st("Hydro Core");
    Ref<spdlog::logger> Log::s_ClientLogger = spdlog::stdout_color_st("Hydro Client");

    spdlog::logger& Log::GetCoreLogger()
    {
        return *s_CoreLogger;
    }

    spdlog::logger& Log::GetClientLogger()
    {
        return *s_ClientLogger;
    }

    void Log::Init()
    {
        s_CoreLogger->set_pattern("%^[%T]: [CORE] %v%$");
        s_CoreLogger->set_level(spdlog::level::trace);

        s_ClientLogger->set_pattern("%^[%T]: [CLIENT] %v%$");
        s_ClientLogger->set_level(spdlog::level::trace);
    }
}
