#include "Shader.h"

#include "Application.h"
#include "Assertion.h"
#include "Log.h"
#include "LogVerbosity.h"
#include "Platform/PlatformShader.h"
#include "Macros.h"
#include "PopupMessage.h"

namespace Hydro
{
    std::string Shader::GetFilename() const
    {
        return m_Filepath.stem().string();
    }
    
    Ref<Shader> Shader::Create(const std::string& Name, const Path& Filepath, ShaderSourceLanguage Language)
    {
        HYDRO_RHI_PLATFORM_RETURN(Shader, Name, Filepath, Language);
    }


    Ref<Shader> Shader::Create(const std::string& Name, const Buffer<u8>& Buffer, ShaderSourceLanguage Language)
    {
        HYDRO_RHI_PLATFORM_RETURN(Shader, Name, Buffer, Language);
    }

    Ref<Shader> Shader::Create(const std::string& Name, const ShaderSource& ShaderSource, ShaderSourceLanguage Language)
    {
        HYDRO_RHI_PLATFORM_RETURN(Shader, Name, ShaderSource, Language);
    }

    Shader::Shader(std::string Name, Path Filepath, ShaderSourceLanguage Language)
        : m_Name(std::move(Name)), m_Filepath(std::move(Filepath)), m_SourceLanguage(Language)
    {
        const Path AbsolutePath = weakly_canonical(m_Filepath);
        const std::string ShaderName = GetName();
        HYDRO_LOG(Shader, Verbosity::Trace, "Loading shader source: {}", ShaderName);
        
        if(!File::Exists(AbsolutePath))
        {
            constexpr std::string_view Message("Cannot load shader: File doesn't exist!");
            HYDRO_LOG(Shader, Verbosity::Error, Message);
            HYDRO_LOG(Shader, Verbosity::Error, "File: {}", m_Filepath.string());
            return;
        }
        
        const std::string FileContent = File::ReadToString(AbsolutePath);
        SplitSources(FileContent);

        HYDRO_LOG(Shader, Verbosity::Trace, "Preprocessing shader \"{}\"", ShaderName);
        if(!Preprocess(m_Source.Vertex) || !Preprocess(m_Source.Fragment))
        {
            HYDRO_LOG(Shader, Verbosity::Info, "Shader preprocess failed. File {}.", ShaderName);
            return;
        }
        
        HYDRO_LOG(Shader, Verbosity::Info, "Shader successfully loaded shader source from: {}", ShaderName);
    }
    

    Shader::Shader(std::string Name, const Buffer<u8>& Buffer, ShaderSourceLanguage Language)
        : m_Name(std::move(Name)), m_SourceLanguage(Language)
    {
        const std::string Source((const char*)Buffer.GetData(), Buffer.Count());
        HYDRO_LOG(Shader, Verbosity::Trace, "Loading shader source from memory");
        SplitSources(Source);
        HYDRO_LOG(Shader, Verbosity::Info, "Shader successfully loaded shader source from memory!");
    }

    Shader::Shader(std::string Name, const ShaderSource& ShaderSource, ShaderSourceLanguage Language)
        : m_Name(std::move(Name)), m_Source(ShaderSource), m_SourceLanguage(Language)
    {
    }

    void Shader::LoadSource(Path Filepath, ShaderSourceLanguage Language)
    {
        m_Filepath = std::move(Filepath);

        const Path AbsolutePath = weakly_canonical(m_Filepath);
        const std::string ShaderName = GetName();
        HYDRO_LOG(Shader, Verbosity::Trace, "Loading shader source: {}", ShaderName);
        
        if(!File::Exists(AbsolutePath))
        {
            constexpr std::string_view Message("Cannot load shader: File doesn't exist!");
            HYDRO_LOG(Shader, Verbosity::Error, Message);
            HYDRO_LOG(Shader, Verbosity::Error, "File: {}", m_Filepath.string());
            return;
        }
        
        const std::string FileContent = File::ReadToString(AbsolutePath);
        SplitSources(FileContent);

        HYDRO_LOG(Shader, Verbosity::Trace, "Preprocessing shader \"{}\"", ShaderName);
        if(!Preprocess(m_Source.Vertex) || !Preprocess(m_Source.Fragment))
        {
            HYDRO_LOG(Shader, Verbosity::Info, "Shader preprocess failed. File {}.", ShaderName);
            return;
        }
        
        HYDRO_LOG(Shader, Verbosity::Info, "Shader successfully loaded shader source from: {}", ShaderName);
    }

    void Shader::SplitSources(const std::string& Source)
    {
        const std::string PragmaVertex = "#pragma vertex";
        const std::string PragmaFragment = "#pragma fragment";
        const std::streamoff VertexShaderPosition = (std::streamoff)Source.find(PragmaVertex);
        const std::streamoff FragmentShaderPosition = (std::streamoff)Source.find(PragmaFragment);
        HYDRO_ASSERT(VertexShaderPosition != -1 || FragmentShaderPosition != -1, "Please use #pragma directives to tell the shader compiler what is the shader type");
        m_Source.Vertex = Source.substr(VertexShaderPosition, FragmentShaderPosition - VertexShaderPosition);
        m_Source.Fragment = Source.substr(FragmentShaderPosition);
        m_Source.Vertex = m_Source.Vertex.substr(PragmaVertex.size() + 1);
        m_Source.Fragment = m_Source.Fragment.substr(PragmaFragment.size() + 1);
    }

    bool Shader::Preprocess(std::string& Source)
    {
        std::stringstream SS(Source);
        while (SS.good())
        {
            std::string Line;
            std::getline(SS, Line);
            if(!Line.starts_with("#include"))
                continue;

            
            char IncludeBuffer[HYDRO_FILENAME_MAX_LENGTH]{};
            (void)sscanf(Line.c_str(), "#include \"%s", IncludeBuffer);

            std::string IncludeStr(IncludeBuffer);
            std::erase(IncludeStr, '"');
            const Path Directory = m_Filepath.parent_path();
            const Path IncludePath = weakly_canonical(weakly_canonical(Directory) / Path(IncludeStr));
            if(!File::Exists(IncludePath))
            {
                HYDRO_LOG(Shader, Verbosity::Error, "Failed to preprocess shader: File {} dooesn't exist!", IncludePath.string());
                return false;
            }

            std::string IncludeContent = File::ReadToString(IncludePath);
            const size_t Position = Source.find(Line);
            Source.replace(Position, Line.size(), IncludeContent);
        }

        return true;
    }

    std::string Shader::GetName()
    {
        return m_Filepath.string().empty() ? m_Name : m_Filepath.string();
    }
}

