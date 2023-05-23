#include "HydroPCH.h"
#include "Filesystem.h"

namespace Hydro::Filesystem
{
    bool File::Exists(const String& filepath)
    {
       return std::filesystem::exists({*filepath});
    }

    bool File::Exists(const std::filesystem::path& filepath)
    {
        return exists(filepath);
    }
}
