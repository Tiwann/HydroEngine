#include "Filesystem.h"
#include "Application.h"
#include "Log.h"
#include "LogVerbosity.h"
#include "Window.h"

#include <GLFW/glfw3native.h>

#if defined(HYDRO_PLATFORM_WINDOWS)
#include <commdlg.h>
#endif

#include <fstream>

namespace Hydro
{
    bool File::Exists(const Path& Filepath)
    {
        return exists(Filepath);
    }

    bool File::Create(const Path& Filepath)
    {
        HYDRO_LOG(Filesystem, Verbosity::Warning, "Creating file: {}", Filepath.string());
        FILE* file = fopen(Filepath.string().c_str(), "w");
        if(!file) return false;
        
        (void)fseek(file, 0, SEEK_END);
        const size_t FileSize = ftell(file);
        if(FileSize > 0) return false;
        
        (void)fclose(file);
        return true;
    }

    Buffer<uint8_t> File::ReadToBuffer(const Path& Filepath)
    {
        FILE* File = fopen(Filepath.string().c_str(), "rb");
        if(!File)
        {
            HYDRO_LOG(Filesystem, Verbosity::Error, "Failed to read file {} into buffer: File doesn't exist!", Filepath.string());
            return {};
        }

        (void)fseek(File, 0, SEEK_END);
        const size_t FileSize = ftell(File);
        (void)fseek(File, 0, SEEK_SET);

        HYDRO_LOG(Filesystem, Verbosity::Warning, "Reading file to buffer: {}. Size: {}", Filepath.string(), BytesToString(FileSize));
        Buffer<uint8_t> OutBuffer(FileSize);
        (void)fread(OutBuffer.GetData(), 1, FileSize, File);
        (void)fclose(File);
        return OutBuffer;
    }

    std::string File::ReadToString(const Path& Filepath)
    {
        HYDRO_LOG(Filesystem, Verbosity::Trace, "Reading file to string: {}", Filepath.string());
        std::ifstream File(Filepath, std::ios::in);
        if(!File.is_open())
        {
            HYDRO_LOG(Filesystem, Verbosity::Error, "Failed to read file {} into string: File doesn't exist!", Filepath.string());
            return "";
        }

        std::stringstream StringStream;
        StringStream << File.rdbuf();
        File.close();
        return StringStream.str();
    }

    Path File::OpenFileDialog(const std::string& Title, const Path& DefaultPath, const char* Filters)
    {
        const Ref<Window>& Window = g_Application->GetWindow();
#if defined HYDRO_PLATFORM_WINDOWS
        OPENFILENAMEA OpenFileName = { };
        ZeroMemory(&OpenFileName, sizeof(OPENFILENAME));
        CHAR szFile[HYDRO_FILENAME_MAX_LENGTH] = { 0 };
        OpenFileName.hwndOwner = glfwGetWin32Window(Window->GetNativeWindow());
        OpenFileName.lStructSize = sizeof(OPENFILENAME);
        OpenFileName.lpstrFile = szFile;
        OpenFileName.nMaxFile = HYDRO_FILENAME_MAX_LENGTH;
        OpenFileName.lpstrFilter = Filters;
        OpenFileName.nFilterIndex = 1;
        OpenFileName.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
        OpenFileName.lpstrInitialDir = DefaultPath.string().c_str();
        OpenFileName.lpstrTitle = Title.c_str();
        return GetOpenFileNameA(&OpenFileName) ? OpenFileName.lpstrFile : "";

#elif defined HYDRO_PLATFORM_UNIX
        return "";
#endif
    }

    Path File::SaveFileDialog(const std::string& Title, const Path& DefaultPath, const char* Filters)
    {
        const Ref<Window>& Window = g_Application->GetWindow();
#if defined HYDRO_PLATFORM_WINDOWS
        OPENFILENAMEA OpenFileName = { };
        ZeroMemory(&OpenFileName, sizeof(OPENFILENAME));
        CHAR szFile[HYDRO_FILENAME_MAX_LENGTH] = { 0 };
        OpenFileName.hwndOwner = glfwGetWin32Window(Window->GetNativeWindow());
        OpenFileName.lStructSize = sizeof(OPENFILENAME);
        OpenFileName.lpstrFile = szFile;
        OpenFileName.nMaxFile = HYDRO_FILENAME_MAX_LENGTH;
        OpenFileName.lpstrFilter = Filters;
        OpenFileName.nFilterIndex = 1;
        OpenFileName.Flags = OFN_CREATEPROMPT | OFN_NOCHANGEDIR | OFN_OVERWRITEPROMPT | OFN_NOLONGNAMES | OFN_EXTENSIONDIFFERENT;
        OpenFileName.lpstrInitialDir = DefaultPath.string().c_str();
        OpenFileName.lpstrTitle = Title.c_str();
        return GetSaveFileNameA(&OpenFileName) ? OpenFileName.lpstrFile : "";
#elif defined HYDRO_PLATFORM_LINUX
        HYDRO_ASSERT(false, "NOT IMPLEMENTED!");
#endif
    }

    std::string File::BytesToString(uint64_t Bytes)
    {
        constexpr uint64_t GB = 1024 * 1024 * 1024;
        constexpr uint64_t MB = 1024 * 1024;
        constexpr uint64_t KB = 1024;

        char buffer[32 + 1] {};

        if (Bytes > GB)
            (void)snprintf(buffer, 32, "%.2f GB", (float)Bytes / (float)GB);
        else if (Bytes > MB)
            (void)snprintf(buffer, 32, "%.2f MB", (float)Bytes / (float)MB);
        else if (Bytes > KB)
            (void)snprintf(buffer, 32, "%.2f KB", (float)Bytes / (float)KB);
        else
            (void)snprintf(buffer, 32, "%.2f Bytes", (float)Bytes);

        return buffer;
    }

    Path File::GetDirectory(const Path& Filepath)
    {
        return Filepath.parent_path();
    }

    bool Directory::Exists(const Path& Directory)
    {
        if(!std::filesystem::is_directory(Directory))
            return false;
        return std::filesystem::exists(Directory);
    }

    bool Directory::Create(const Path& Directory)
    {
        return std::filesystem::create_directory(Directory);
    }

    Path Directory::OpenFolderDialog(const Path& DefaultPath, const std::string& Title)
    {
        return "";
    }

    std::vector<Path> Directory::GetFiles(const Path& Directory)
    {
        if(!is_directory(Directory) || !Exists(Directory))
            return {};

        std::vector<Path> Result;
        for(const auto& Filepath : std::filesystem::directory_iterator(Directory))
        {
            if(is_regular_file(Filepath))
            {
                Result.push_back(Filepath);
            }
        }
        return Result;
    }

    Path Directory::GetUserDirectory()
    {
#if defined(HYDRO_PLATFORM_WINDOWS)
        CHAR DirectoryPath[HYDRO_FILENAME_MAX_LENGTH] = { 0 };
        const DWORD DirectoryPathLength = GetEnvironmentVariableA("USERPROFILE", DirectoryPath, HYDRO_FILENAME_MAX_LENGTH);
        const std::string_view DirectoryStr(DirectoryPath, DirectoryPathLength);
        return DirectoryStr;
#elif defined(HYDRO_PLATFORM_UNIX)
        return getenv("HOME");
#endif
    }
}


