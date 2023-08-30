#pragma once
#include "Core/Shader.h"
#include "Core/ShaderSourceLanguage.h"
#include "shaderc/shaderc.h"

namespace Hydro
{
    class OpenGLShader : public Shader
    {
    public:
        OpenGLShader(Path Filepath, ShaderSourceLanguage Language);
        bool Compile() override;
        bool Link() override;
        bool Validate() override;
        bool UseProgram() override;
    protected:
        uint32_t m_Program;
        uint32_t m_VertexHandle;
        uint32_t m_FragmentHandle;
    private:
        static uint32_t ShadercToOpenGL(shaderc_shader_kind Kind);
        static shaderc_shader_kind OpenGLToShaderc(uint32_t Type);
    };
}
