#pragma once
#include "Buffer.h"
#include "LogCategory.h"
#include <string>

namespace Hydro
{
    using Path = std::filesystem::path;
    HYDRO_DECLARE_LOG_CATEGORY_STATIC(Filesystem, "FILESYSTEM")
    
    
    class File
    {
    public:
        static bool Exists(const Path& Filepath);
        static bool Create(const Path& Filepath);
        static Buffer<uint8_t> ReadToBuffer(const Path& Filepath);
        static std::string ReadToString(const Path& Filepath);
        static Path OpenFileDialog(const std::string& Title, const Path& DefaultPath, const char* Filters);
        static std::string BytesToString(uint64_t Bytes);
    };

    class Directory
    {
    public:
        static bool Exists(const Path& Directory);
        static bool Create(const Path& Directory);
        static Path OpenFolderDialog(const Path& DefaultPath, const std::string& Title);
        static Path GetUserDirectory();
    };
}
