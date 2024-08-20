#pragma once
#include "Buffer.h"
#include "LogCategory.h"
#include <string>
#include <filesystem>

namespace Hydro
{
    using Path = std::filesystem::path;
    HYDRO_DECLARE_LOG_CATEGORY_STATIC(Filesystem, "FILESYSTEM")
    
    
    class File
    {
    public:
        File() = delete;
        static bool Exists(const Path& Filepath);
        static bool Create(const Path& Filepath);
        static Buffer<uint8_t> ReadToBuffer(const Path& Filepath);
        static std::string ReadToString(const Path& Filepath);
        static Path OpenFileDialog(const std::string& Title, const Path& DefaultPath, const char* Filters);
        static Path SaveFileDialog(const std::string& Title, const Path& DefaultPath, const char* Filters);
        static std::string BytesToString(uint64_t Bytes);
        static Path GetDirectory(const Path& Filepath);
    };

    class Directory
    {
    public:
        Directory() = delete;
        static bool Exists(const Path& Directory);
        static bool Create(const Path& Directory);
        static Path OpenFolderDialog(const Path& DefaultPath, const std::string& Title);
        static std::vector<Path> GetFiles(const Path& Directory);
        static Path GetUserDirectory();
    };
}
