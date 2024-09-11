#pragma once
#include "String.h"
#include "StringView.h"

#include <spdlog/fmt/bundled/core.h>
#include <spdlog/fmt/bundled/format.h>

namespace Hydro
{
    template <typename... Args>
    String Format(const fmt::format_string<Args...>& Fmt, Args&&... Arguments)
    {
        return fmt::vformat(Fmt, fmt::make_format_args(Arguments...)).c_str();
    }
}

namespace fmt
{
    template<>
    struct formatter<Hydro::String> : formatter<string_view>
    {
        format_context::iterator format(const Hydro::String& Str, format_context& Context) const
        {
            return formatter<string_view>::format(string_view(Str.Data(), Str.Count()), Context);
        }
    };

    template<>
    struct formatter<Hydro::StringView> : formatter<string_view>
    {
        format_context::iterator format(const Hydro::StringView& Str, format_context& Context) const
        {
            return formatter<string_view>::format(string_view(Str.Data(), Str.Count()), Context);
        }
    };
}
