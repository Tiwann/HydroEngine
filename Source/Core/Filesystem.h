#pragma once
#include "String.h"

namespace Hydro::Filesystem
{
    class HYDRO_API File
    {
    public:
        static bool Exists(const String& filepath);
        static bool Exists(const std::filesystem::path& filepath);
    };
}
