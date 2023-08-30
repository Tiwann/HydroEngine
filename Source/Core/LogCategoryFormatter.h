#pragma once
#include "Macros.h"
#include "spdlog/pattern_formatter.h"

namespace Hydro
{
    class HYDRO_API LogCategoryFormatter : public spdlog::custom_flag_formatter
    {
    public:
        void format(const spdlog::details::log_msg& msg, const std::tm& tm_time, spdlog::memory_buf_t& dest) override;
        std::unique_ptr<custom_flag_formatter> clone() const override;
    };    
}
