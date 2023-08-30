#pragma once
#include "Core/Filesystem.h"
#include "Macros.h"
#include "Core/ShaderSource.h"
#include "Core/ShaderSourceLanguage.h"
#include "Core/LogCategory.h"
#include "Core/SharedPointer.h"

HYDRO_DECLARE_LOG_CATEGORY_STATIC(Shader, "SHADER");

namespace Hydro
{
    class HYDRO_API Shader
    {
    public:
        virtual bool Compile() = 0;
        virtual bool Link() = 0;
        virtual bool Validate() = 0;
        virtual bool UseProgram() = 0;
        std::string GetFilename() const;

        static Shader* Create(const Path& Filepath, ShaderSourceLanguage Language);
    protected:
        Shader(Path Filepath, ShaderSourceLanguage Language);
        virtual ~Shader() = default;

        Path m_Filepath;
        ShaderSource m_Source;
        ShaderSourceLanguage m_SourceLanguage;

        bool Compiled{false};
        bool Linked{false};
        bool Validated{false};
    };


    
}
