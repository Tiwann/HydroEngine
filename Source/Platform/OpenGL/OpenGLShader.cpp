#include "HydroPCH.h"
#include "OpenGLShader.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include "glad/gl.h"

namespace Hydro
{
    OpenGLShader::OpenGLShader(const String& filepath)
    {
        m_Filepath = filepath;
        if(!m_Filepath.EndsWith(".glsl"))
        {
            std::cout << "File: " << filepath << "is not a .glsl file!\n";
            return;
        }
        std::stringstream ss;
        ss << std::ifstream(*m_Filepath, std::ios::binary).rdbuf();

        const String wholefile = ss.str().c_str();
        
        const unsigned int vertpos = wholefile.Find("#pragma vertex");
        const unsigned int fragpos = wholefile.Find("#pragma fragment");

        m_VertexSource = wholefile.SubString(0, fragpos);
        m_FragSource = wholefile.SubString(fragpos, wholefile.Size() - fragpos);

        m_VertexSource.Erase(0, sizeof("#pragma vertex\n"));
        m_FragSource.Erase(0, sizeof("#pragma fragment\n"));

        if(m_VertexSource.IsEmpty() || m_FragSource.IsEmpty())
        {
            std::cout << "Failed to parse glsl file: " << *m_Filepath << '\n';
            return;
        }

        const char* vs = *m_VertexSource;
        const char* fs = *m_FragSource;
        
        m_VertexShaderHandle = glCreateShader(GL_VERTEX_SHADER);
        m_FragShaderHandle = glCreateShader(GL_FRAGMENT_SHADER);

        glShaderSource(m_VertexShaderHandle, 1, &vs, nullptr);
        glShaderSource(m_FragShaderHandle, 1, &fs, nullptr);

        m_ProgramHandle = glCreateProgram();
        glAttachShader(m_ProgramHandle, m_VertexShaderHandle);
        glAttachShader(m_ProgramHandle, m_FragShaderHandle);
    }

    bool OpenGLShader::Compile()
    {
        int success = false;
        
        glCompileShader(m_VertexShaderHandle);
        glGetShaderiv(m_VertexShaderHandle, GL_COMPILE_STATUS,&success);

        if(!success)
        {
            char message[1024];
            int length;
            glGetShaderInfoLog(m_VertexShaderHandle, 1024, &length, message);
            std::cout << "Failed to compile vertex shader!\n" << std::string(message, length) << '\n';
            return m_Compiled = false;
        }

        glCompileShader(m_FragShaderHandle);
        glGetShaderiv(m_FragShaderHandle, GL_COMPILE_STATUS,&success);

        if(!success)
        {
            char message[1024];
            int length;
            glGetShaderInfoLog(m_FragShaderHandle, 1024, &length, message);
            std::cout << "Failed to compile fragment shader!\n" << std::string(message, length) << '\n';
            return m_Compiled = false;
        }

        return  m_Compiled = true;
    }

    bool OpenGLShader::Link()
    {
        if(!m_Compiled)
        {
            std::cout << "Cannot link shader program: " << *m_Filepath << " because a shader failed to compile!";
            return m_Linked = false;
        }
        
        int success = false;
        glLinkProgram(m_ProgramHandle);
        glGetProgramiv(m_ProgramHandle, GL_LINK_STATUS, &success);

        if(!success)
        {
            char message[1024];
            int length;
            glGetProgramInfoLog(m_ProgramHandle, 1024, &length, message);
            std::cout << "Failed to link shader program!\n" << std::string(message, length) << '\n';
            m_Linked = false;
        }

        return m_Linked = true;
    }

    bool OpenGLShader::Validate()
    {
        if(!m_Linked)
        {
            std::cout << "Cannot validate shader program: " << *m_Filepath << " because the program failed to link!";
            return m_Validated = false;
        }
        
        int success = false;
        glValidateProgram(m_ProgramHandle);
        glGetProgramiv(m_ProgramHandle, GL_VALIDATE_STATUS, &success);

        if(!success)
        {
            char message[1024];
            int length;
            glGetProgramInfoLog(m_ProgramHandle, 1024, &length, message);
            std::cout << "Failed to validate shader program!\n" << std::string(message, length) << '\n';
            return m_Validated = false;
        }

        return m_Validated = true;
    }

    void OpenGLShader::UseProgram() const
    {
        if(!(m_Compiled && m_Linked && m_Validated))
        {
            std::cout << "Cannot use this shader program!\n";
            return;
        }

        glUseProgram(m_ProgramHandle);
    }
}
