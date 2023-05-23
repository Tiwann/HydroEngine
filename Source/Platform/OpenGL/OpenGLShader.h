#pragma once
#include "HydroPCH.h"

#include "Core/SharedPointer.h"
#include "Core/String.h"


namespace Hydro
{
    class OpenGLShader
    {
    public:
        OpenGLShader(const struct ShaderSource& sources);
        bool Compile();
        bool Link();
        bool Validate();
        void UseProgram() const;

        static Ref<OpenGLShader> FromFiles(const String& vertexSourcePath, const String& fragmentSourcePath);
    
    private:
        String m_Filepath{};
        String m_VertexSource{};
        String m_FragSource{};
        bool m_Compiled{false};
        bool m_Linked{false};
        bool m_Validated{false};

        Handle m_VertexShaderHandle{0};
        Handle m_FragShaderHandle{0};
        Handle m_ProgramHandle{0};
    };
}
