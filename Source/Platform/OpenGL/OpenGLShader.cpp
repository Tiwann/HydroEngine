﻿#include "OpenGLShader.h"

#include "Core/Assertion.h"
#include "Core/Log.h"
#include "Core/LogVerbosity.h"

#include "Core/Texture2D.h"

#include <glad/gl.h>


namespace Hydro
{
    OpenGLShader::OpenGLShader(const std::string& Name, Path Filepath, ShaderSourceLanguage Language)
        : Shader(Name, std::move(Filepath), Language), m_Program(UINT32_MAX), m_VertexHandle(UINT32_MAX), m_FragmentHandle(UINT32_MAX)
    {
        
    }

    OpenGLShader::OpenGLShader(const std::string& Name, Buffer<u8> Buffer, ShaderSourceLanguage Language)
        : Shader(Name, Buffer, Language), m_Program(UINT32_MAX), m_VertexHandle(UINT32_MAX), m_FragmentHandle(UINT32_MAX)
    {
    }

    OpenGLShader::OpenGLShader(const std::string& Name, const ShaderSource& ShaderSource, ShaderSourceLanguage Language)
        : Shader(Name, ShaderSource, Language), m_Program(UINT32_MAX), m_VertexHandle(UINT32_MAX), m_FragmentHandle(UINT32_MAX)
    {
    }

    OpenGLShader::~OpenGLShader()
    {
        glDeleteShader(m_VertexHandle);
        glDeleteShader(m_FragmentHandle);
        glDeleteProgram(m_Program);
    }

    bool OpenGLShader::CompileOpenGL()
    {
        // Compile Vertex
        {
            const std::string ShaderName = GetName();
            HYDRO_LOG(Shader, Verbosity::Trace, "Compiling vertex shader: {}", ShaderName);
            m_VertexHandle = glCreateShader(GL_VERTEX_SHADER);

            const char* VertexSource = m_Source.Vertex.c_str();
            const i32 VertexSize = (i32)m_Source.Vertex.size();
            glShaderSource(m_VertexHandle, 1, &VertexSource, &VertexSize);
            glCompileShader(m_VertexHandle);
            
            int Success = 0;
            glGetShaderiv(m_VertexHandle, GL_COMPILE_STATUS, &Success);
            if(!Success)
            {
                i32 Length = 0;
                char Message[GL_INFO_LOG_LENGTH];
                glGetShaderInfoLog(m_VertexHandle, GL_INFO_LOG_LENGTH, &Length, Message);
                HYDRO_LOG(Shader, Verbosity::Error, "Failed to compile vertex shader: {}", Message);
                return false;
            }
            
            HYDRO_LOG(Shader, Verbosity::Info, "Successfully compiled vertex shader!");
        }

        // Compile Fragment
        {
            const std::string ShaderName = GetName();
            HYDRO_LOG(Shader, Verbosity::Trace, "Compiling fragment shader: {}", ShaderName);
            m_FragmentHandle = glCreateShader(GL_FRAGMENT_SHADER);

            const char* FragmentSource = m_Source.Fragment.c_str();
            const i32 FragmentSize = (i32)m_Source.Fragment.size();
            glShaderSource(m_FragmentHandle, 1, &FragmentSource, &FragmentSize);
            glCompileShader(m_FragmentHandle);
            
            int Success = 0;
            glGetShaderiv(m_FragmentHandle, GL_COMPILE_STATUS, &Success);
            if(!Success)
            {
                i32 Length = 0;
                char Message[GL_INFO_LOG_LENGTH];
                glGetShaderInfoLog(m_FragmentHandle, GL_INFO_LOG_LENGTH, &Length, Message);
                HYDRO_LOG(Shader, Verbosity::Error, "Failed to compiled fragment shader: {}", Message);
                return false;
            }

            HYDRO_LOG(Shader, Verbosity::Info, "Successfully compiled fragment shader!");
        }
        return true;
    }
    
    bool OpenGLShader::Compile()
    {
        Compiled =
#if defined(HYDRO_USE_DEFAULT_OPENGL_SHADER_COMPILER)
        CompileOpenGL();
#else
        CompileShaderc();
#endif
        m_Program = glCreateProgram();
        glAttachShader(m_Program, m_VertexHandle);
        glAttachShader(m_Program, m_FragmentHandle);
        return Compiled;
    }

    bool OpenGLShader::Link()
    {
        if(!Compiled)
        {
            HYDRO_LOG(Shader, Verbosity::Error, "Shader program failed to link: One or more shader(s) failed to compile!");
            return Linked = false;
        }
        
        glLinkProgram(m_Program);
        i32 Success = 0;
        glGetProgramiv(m_Program, GL_LINK_STATUS, &Success);
        if(!Success)
        {
            i32 Length = 0;
            char Message[GL_INFO_LOG_LENGTH];
            glGetProgramInfoLog(m_Program, GL_INFO_LOG_LENGTH, &Length, Message);
            HYDRO_LOG(Shader, Verbosity::Error, "Shader program failed to link: {}", Message);
            return Linked = Success;
        }
        const auto ShaderName = GetName();
        HYDRO_LOG(Shader, Verbosity::Info, "Shader program {} successfully linked!", ShaderName);
        return Linked = Success;
    }

    bool OpenGLShader::Validate()
    {
        if(!Linked)
        {
            HYDRO_LOG(Shader, Verbosity::Error, "Shader program failed to validate: Shader program failed to link!");
            return Validated = false;
        }
        glValidateProgram(m_Program);
        i32 Success = 0;
        glGetProgramiv(m_Program, GL_VALIDATE_STATUS, &Success);
        if(!Success)
        {
            i32 Length = 0;
            char Message[GL_INFO_LOG_LENGTH];
            glGetProgramInfoLog(m_Program, GL_INFO_LOG_LENGTH, &Length, Message);
            HYDRO_LOG(Shader, Verbosity::Error, "Shader program failed to validate: {}", Message);
            return Validated = Success;
        }
        const auto ShaderName = GetName();
        HYDRO_LOG(Shader, Verbosity::Info, "Shader program {} successfully validated!", ShaderName);
        return Validated = Success;
    }

    bool OpenGLShader::Bind()
    {
        if(!Validated)
        {
            HYDRO_LOG(Shader, Verbosity::Error, "Cannot use this shader: Not a valid shader!");
            return false;
        }

        glUseProgram(m_Program);
        return true;
    }

    void OpenGLShader::Delete()
    {
        glDeleteShader(m_VertexHandle);
        glDeleteShader(m_FragmentHandle);
        glDeleteProgram(m_Program);
    }
    
    #define HYDRO_SHADER_UNIFORM_CHECK(Uniform, Name) \
        if((Uniform) == -1) \
        { \
            HYDRO_LOG(Shader, Verbosity::Error, "Uniform \"{}\" doesn't exist in shader \"{}\"", (Name), m_Name); \
            return; \
        }((void)0)
    
    
    void OpenGLShader::SetUniformFloat(const std::string& Name, f32 Value)
    {
        const i32 Location = glGetUniformLocation(m_Program, Name.c_str());
        HYDRO_SHADER_UNIFORM_CHECK(Location, Name);
        glUniform1f(Location, Value);
    }
    

    void OpenGLShader::SetUniformFloat2(const std::string& Name, const Vector2& Value)
    {
        const i32 Location = glGetUniformLocation(m_Program, Name.c_str());
        HYDRO_SHADER_UNIFORM_CHECK(Location, Name);
        glUniform2f(Location, Value.x, Value.y);
    }

    void OpenGLShader::SetUniformFloat3(const std::string& Name, const Vector3& Value)
    {
        const i32 Location = glGetUniformLocation(m_Program, Name.c_str());
        HYDRO_SHADER_UNIFORM_CHECK(Location, Name);
        glUniform3f(Location, Value.x, Value.y, Value.z);
    }

    void OpenGLShader::SetUniformFloat4(const std::string& Name, const Vector4& Value)
    {
        const i32 Location = glGetUniformLocation(m_Program, Name.c_str());
        HYDRO_SHADER_UNIFORM_CHECK(Location, Name);
        glUniform4fv(Location, 1, (const f32*)&Value);
    }

    void OpenGLShader::SetUniformMat4(const std::string& Name, const Matrix4& Value)
    {
        const i32 Location = glGetUniformLocation(m_Program, Name.c_str());
        HYDRO_SHADER_UNIFORM_CHECK(Location, Name);
        glUniformMatrix4fv(Location, 1, false, (const f32*)&Value);
    }

    void OpenGLShader::SetUniformInt(const std::string& Name, i32 Value)
    {
        const i32 Location = glGetUniformLocation(m_Program, Name.c_str());
        HYDRO_SHADER_UNIFORM_CHECK(Location, Name);
        glUniform1i(Location, Value);
    }

    void OpenGLShader::SetUniformTexture(const std::string& Name, const Ref<Texture2D>& Texture)
    {
        if(!Texture)
        {
            HYDRO_LOG(Shader, Verbosity::Error, "Tried to upload a nullptr texture to a shader!");
            return;
        }
        Texture->Bind();
        SetUniformInt(Name, (i32)Texture->GetSlot());
    }

    void OpenGLShader::SetUniformMat2(const std::string& Name, const Matrix2& Value)
    {
        const i32 Location = glGetUniformLocation(m_Program, Name.c_str());
        HYDRO_SHADER_UNIFORM_CHECK(Location, Name);
        glUniformMatrix2fv(Location, 1, false, (const f32*)&Value);
    }

    void OpenGLShader::SetUniformMat3(const std::string& Name, const Matrix3& Value)
    {
        const i32 Location = glGetUniformLocation(m_Program, Name.c_str());
        HYDRO_SHADER_UNIFORM_CHECK(Location, Name);
        glUniformMatrix3fv(Location, 1, false, (const f32*)&Value);
    }

    f32 OpenGLShader::GetUniformFloat(const std::string& Name)
    {
        const i32 Location = glGetUniformLocation(m_Program, Name.c_str());
        if(!Location) \
        { \
            HYDRO_LOG(Shader, Verbosity::Error, "Uniform \"{}\" doesn't exist in shader \"{}\"", (Name), m_Name); \
            HYDRO_LOG(Shader, Verbosity::Error, "Path: {}", m_Filepath.string()); \
            return 0.0f; \
        }

        f32 Result;
        glGetUniformfv(m_Program, Location, &Result);
        return Result;
    }

    Vector2 OpenGLShader::GetUniformFloat2(const std::string& Name)
    {
        const i32 Location = glGetUniformLocation(m_Program, Name.c_str());
        if(!Location) \
        { \
            HYDRO_LOG(Shader, Verbosity::Error, "Uniform \"{}\" doesn't exist in shader \"{}\"", (Name), m_Name); \
            HYDRO_LOG(Shader, Verbosity::Error, "Path: {}", m_Filepath.string()); \
            return {0.0f}; \
        }

        Vector2 Result;
        glGetnUniformfv(m_Program, Location, 2 * sizeof(f32), (f32*)&Result);
        return Result;
    }

    Vector3 OpenGLShader::GetUniformFloat3(const std::string& Name)
    {
        const i32 Location = glGetUniformLocation(m_Program, Name.c_str());
        if(!Location) \
        { \
            HYDRO_LOG(Shader, Verbosity::Error, "Uniform \"{}\" doesn't exist in shader \"{}\"", (Name), m_Name); \
            HYDRO_LOG(Shader, Verbosity::Error, "Path: {}", m_Filepath.string()); \
            return {0.0f}; \
        }

        Vector3 Result;
        glGetnUniformfv(m_Program, Location, 3 * sizeof(f32), (f32*)&Result);
        return Result;
    }

    Vector4 OpenGLShader::GetUniformFloat4(const std::string& Name)
    {
        const i32 Location = glGetUniformLocation(m_Program, Name.c_str());
        if(!Location) \
        { \
            HYDRO_LOG(Shader, Verbosity::Error, "Uniform \"{}\" doesn't exist in shader \"{}\"", (Name), m_Name); \
            HYDRO_LOG(Shader, Verbosity::Error, "Path: {}", m_Filepath.string()); \
            return {0.0f}; \
        }

        Vector4 Result;
        glGetnUniformfv(m_Program, Location, 4 * sizeof(f32), (f32*)&Result);
        return Result;
    }

    Matrix4 OpenGLShader::GetUniformMat4(const std::string& Name)
    {
        const i32 Location = glGetUniformLocation(m_Program, Name.c_str());
        if(!Location) \
        { \
            HYDRO_LOG(Shader, Verbosity::Error, "Uniform \"{}\" doesn't exist in shader \"{}\"", (Name), m_Name); \
            HYDRO_LOG(Shader, Verbosity::Error, "Path: {}", m_Filepath.string()); \
            return Matrix4::Identity; \
        }

        Matrix4 Result;
        glGetnUniformfv(m_Program, Location, 4 * 4 * sizeof(f32), (f32*)&Result);
        return Result;
    }

    i32 OpenGLShader::GetUniformInt(const std::string& Name)
    {
        const i32 Location = glGetUniformLocation(m_Program, Name.c_str());
        if(!Location) \
        { \
            HYDRO_LOG(Shader, Verbosity::Error, "Uniform \"{}\" doesn't exist in shader \"{}\"", Name, m_Name); \
            HYDRO_LOG(Shader, Verbosity::Error, "Path: {}", m_Filepath.string()); \
            return 0; \
        }

        i32 Result;
        glGetUniformiv(m_Program, Location, &Result);
        return Result;
    }
}
