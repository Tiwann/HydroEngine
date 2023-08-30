#include "HydroPCH.h"
#include "Shader.h"
#include "Platform/PlatformShader.h"

namespace Hydro
{
    std::string Shader::GetFilename() const
    {
        return m_Filepath.stem().string();
    }

    Shader* Shader::Create(const Path& Filepath, ShaderSourceLanguage Language)
    {
        #if defined(HYDRO_PLATFORM_DIRECTX)
                return nullptr;
        #elif defined(HYDRO_PLATFORM_VULKAN)
                return nullptr;
        #elif defined(HYDRO_PLATFORM_OPENGL)
                return new OpenGLShader(Filepath, Language);
        #endif
    }

    Shader::Shader(Path Filepath, ShaderSourceLanguage Language) :
    m_Filepath(std::move(Filepath)), m_SourceLanguage(Language)
    {
    }
}

