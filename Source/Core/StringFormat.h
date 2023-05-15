#pragma once
#include "String.h"

namespace Hydro
{
    template<typename... Args>
    String Format(const String& format, Args&&... args)
    {
        const size_t size = std::snprintf(nullptr, 0, *format, std::forward<Args>(args)...) + 1;
        char* buffer = new char[size];
        std::snprintf(buffer, size, *format, std::forward<Args>(args)...);
        String result(buffer);
        delete[] buffer;
        return result;
    }

    template<typename... Args>
    WString Format(const WString& format, Args&&... args)
    {
        wchar_t buffer[1024];
        std::swprintf(buffer, 1024, *format, std::forward<Args>(args)...);
        WString result(buffer);
        return result;
    }
}
