#include "HydroPCH.h"
#include "OpenGLShader.h"
#include "ShaderSource.h"
#include "Core/Application.h"
#include "glad/gl.h"


namespace Hydro
{
    OpenGLShader::OpenGLShader(const ShaderSource& sources) :
    m_VertexSource(sources.VertexSource), m_FragSource(sources.FragmentSource)
    {
        if(m_VertexSource.IsEmpty())
        {
            std::cout << "Failed to parse glsl file: Vertex source is empty!" << '\n';
            Application::GetCurrentApplication().RequireExit(false);
        }

        if(m_FragSource.IsEmpty())
        {
            std::cout << "Failed to parse glsl file: Fragement source is empty!" << '\n';
            Application::GetCurrentApplication().RequireExit(false);
        }

        const char* vs = *m_VertexSource;
        const char* fs = *m_FragSource;
        
        m_VertexShaderHandle = glCreateShader(GL_VERTEX_SHADER);
        m_FragShaderHandle = glCreateShader(GL_FRAGMENT_SHADER);

        glShaderSource((GLuint)m_VertexShaderHandle, 1, &vs, nullptr);
        glShaderSource((GLuint)m_FragShaderHandle, 1, &fs, nullptr);

        m_ProgramHandle = glCreateProgram();
        glAttachShader((GLuint)m_ProgramHandle, (GLuint)m_VertexShaderHandle);
        glAttachShader((GLuint)m_ProgramHandle, (GLuint)m_FragShaderHandle);
    }

    bool OpenGLShader::Compile()
    {
        int success = false;
        
        glCompileShader((GLuint)m_VertexShaderHandle);
        glGetShaderiv((GLuint)m_VertexShaderHandle, GL_COMPILE_STATUS,&success);

        if(!success)
        {
            char message[1024];
            int length;
            glGetShaderInfoLog((GLuint)m_VertexShaderHandle, 1024, &length, message);
            std::cout << "Failed to compile vertex shader!\n" << std::string(message, length) << '\n';
            return m_Compiled = false;
        }

        glCompileShader((GLuint)m_FragShaderHandle);
        glGetShaderiv((GLuint)m_FragShaderHandle, GL_COMPILE_STATUS,&success);

        if(!success)
        {
            char message[1024];
            int length;
            glGetShaderInfoLog((GLuint)m_FragShaderHandle, 1024, &length, message);
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
        glLinkProgram((GLuint)m_ProgramHandle);
        glGetProgramiv((GLuint)m_ProgramHandle, GL_LINK_STATUS, &success);

        if(!success)
        {
            char message[1024];
            int length;
            glGetProgramInfoLog((GLuint)m_ProgramHandle, 1024, &length, message);
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
        glValidateProgram((GLuint)m_ProgramHandle);
        glGetProgramiv((GLuint)m_ProgramHandle, GL_VALIDATE_STATUS, &success);

        if(!success)
        {
            char message[1024];
            int length;
            glGetProgramInfoLog((GLuint)m_ProgramHandle, 1024, &length, message);
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

        glUseProgram((GLuint)m_ProgramHandle);
    }

    Ref<OpenGLShader> OpenGLShader::FromFiles(const String& vertexSourcePath, const String& fragmentSourcePath)
    {
        ShaderSource sources;
        
        if(FILE* file = fopen(*vertexSourcePath, "rb"))
        {
            
            fseek(file, 0, SEEK_END);
            const size_t size = ftell(file);
            fseek(file, 0, SEEK_SET);
            char* const buffer = new char[size];
            fread(buffer, 1, size, file);
            sources.VertexSource = buffer;
            delete[] buffer;
        }

        if(FILE* file = fopen(*fragmentSourcePath, "rb"))
        {
            
            fseek(file, 0, SEEK_END);
            const size_t size = ftell(file);
            fseek(file, 0, SEEK_SET);
            char* const buffer = new char[size];
            fread(buffer, 1, size, file);
            sources.FragmentSource = buffer;
            delete[] buffer;
        }

        return CreateRef<OpenGLShader>(sources);
    }
}
