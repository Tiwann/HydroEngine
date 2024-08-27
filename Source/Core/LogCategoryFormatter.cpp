#include "LogCategoryFormatter.h"
#include "Log.h"

namespace Hydro
{
    void LogCategoryFormatter::format(const spdlog::details::log_msg& msg, const std::tm&,
        spdlog::memory_buf_t& dest)
    {
        dest.append(Log::s_CurrentCategoryName);
    }

    std::unique_ptr<spdlog::custom_flag_formatter> LogCategoryFormatter::clone() const
    {
        return spdlog::details::make_unique<LogCategoryFormatter>();
    }
}
