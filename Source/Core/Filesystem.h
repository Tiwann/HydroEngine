#pragma once
#include "Macros.h"

namespace Hydro
{
    using Path = std::filesystem::path;
    class HYDRO_API File
    {
    public:
        static bool Exists(const Path& filepath);
        static bool Create(const Path& Filepath);
    };

    class HYDRO_API Directory
    {
    public:
        static bool Exists(const Path& Directory);
        static bool MakeDirectory(const Path& Directory);
    };
}
