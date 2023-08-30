#include "HydroPCH.h"
#include "Log.h"

#include "spdlog/pattern_formatter.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "LogCategoryFormatter.h"

namespace Hydro
{
    Ref<spdlog::logger> Log::s_CoreLogger = spdlog::stdout_color_st("Hydro Core");
    Ref<spdlog::logger> Log::s_ClientLogger = spdlog::stdout_color_st("Hydro Client");
    
    std::string Log::s_CurrentCategoryName;
    
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
        auto formatter = std::make_unique<spdlog::pattern_formatter>();
        formatter->add_flag<LogCategoryFormatter>('#').set_pattern("%^[%T]: [CORE] [%#] %v%$");
        s_CoreLogger->set_formatter(std::move(formatter));
        s_CoreLogger->set_level(spdlog::level::trace);

        s_ClientLogger->set_pattern("%^[%T]: [CLIENT] [%#] %v%$");
        s_ClientLogger->set_level(spdlog::level::trace);
    }

    void Log::SetCurrentCategoryName(std::string CategoryName)
    {
        s_CurrentCategoryName = std::move(CategoryName);
    }
    
}
