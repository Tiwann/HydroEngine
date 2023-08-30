#include "HydroPCH.h"
#include "Filesystem.h"

namespace Hydro
{
    bool File::Exists(const Path& filepath)
    {
        return std::filesystem::exists(filepath);
    }

    bool File::Create(const Path& Filepath)
    {
        FILE* file = fopen(Filepath.string().c_str(), "w");
        if(!file) return false;
        
        fclose(file);
        return true;
    }

    bool Directory::Exists(const Path& Directory)
    {
        if(!std::filesystem::is_directory(Directory))
            return false;

        return std::filesystem::exists(Directory);
    }

    bool Directory::MakeDirectory(const Path& Directory)
    {
        return std::filesystem::create_directory(Directory);
    }
}


