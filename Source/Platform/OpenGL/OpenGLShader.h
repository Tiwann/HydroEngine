#pragma once
#include "HydroPCH.h"
#include "Core/String.h"

namespace Hydro
{
    class OpenGLShader
    {
    public:
        OpenGLShader(const String& filepath);
        bool Compile();
        bool Link();
        bool Validate();
        void UseProgram() const;
    
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
