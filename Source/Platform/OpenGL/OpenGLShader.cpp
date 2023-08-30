#include "HydroPCH.h"
#include "OpenGLShader.h"

#include "Core/Assertion.h"
#include "shaderc/shaderc.hpp"
#include "Core/Log.h"
#include "Core/ShaderCache.h"
#include "glad/gl.h"

#include <fstream>

#include "Core/ShaderUtils.h"
#include "Core/LogVerbosity.h"
#include "OpenGLDevice.h"

namespace Hydro
{
    OpenGLShader::OpenGLShader(Path Filepath, ShaderSourceLanguage Language)
        : Shader(std::move(Filepath), Language), m_Program(UINT32_MAX), m_VertexHandle(UINT32_MAX), m_FragmentHandle(UINT32_MAX)
    {
        HYDRO_LOG(Shader, Trace, "Loading shader source: {}", m_Filepath.string());

       
        //TODO: Retrieve Cached shaders
        if(!File::Exists(m_Filepath))
        {
            HYDRO_LOG(Shader, Error, "Cannot load shader: File doesn't exist!");
            HYDRO_LOG(Shader, Error, "File: {}", m_Filepath.string());
            return;
        }
        
        std::ifstream Stream(m_Filepath, std::ios::in);
        if(!Stream.is_open())
        {
            HYDRO_LOG(Shader, Error, "Failed to load shader: Stream failed to open!");
            return;
        }

        std::stringstream StringStream;
        StringStream << Stream.rdbuf();
        std::string FileContent = StringStream.str();
        Stream.close();
        StringStream.clear();

        const std::string PragmaVertex = "#pragma vertex";
        const std::string PragmaFragment = "#pragma fragment";
        const std::streamoff VertexShaderPosition = FileContent.find(PragmaVertex);
        const std::streamoff FragmentShaderPosition = FileContent.find(PragmaFragment);
        HYDRO_ASSERT(VertexShaderPosition != -1 || FragmentShaderPosition != -1, "Please use #pragma directives to tell the shader compiler what is the shader type");
        m_Source.Vertex = FileContent.substr(VertexShaderPosition, FragmentShaderPosition - VertexShaderPosition);
        m_Source.Fragment = FileContent.substr(FragmentShaderPosition);
        m_Source.Vertex.erase(PragmaVertex.size());
        m_Source.Fragment.erase(PragmaFragment.size());
        
        HYDRO_LOG(Shader, Info, "Shader successfully loaded shader source from: {}", m_Filepath.string());
    }

    bool OpenGLShader::Compile()
    {
        shaderc::CompileOptions Options = ShaderUtils::CreateShadercCompileOptions(m_SourceLanguage);
        const shaderc::Compiler Compiler;

        // Compile Vertex
        {
            HYDRO_LOG(Shader, Trace, "Compiling vertex shader: {}", m_Filepath.string());
            const std::string ShaderID = fmt::format("{}.vert", m_Filepath.stem().string());
            const shaderc::SpvCompilationResult Result = Compiler.CompileGlslToSpv(m_Source.Vertex, shaderc_vertex_shader, ShaderID.c_str(), "main", Options);
            
            if (Result.GetCompilationStatus() != shaderc_compilation_status_success || Result.GetNumWarnings() != 0)
            {
                HYDRO_LOG(Shader, Error, "Vertex Shader {} failed to compile!", m_Filepath.filename().string());
                HYDRO_LOG(Shader, Error, Result.GetErrorMessage().erase(Result.GetErrorMessage().size() - 1));
                return Compiled = false;
            }
            HYDRO_LOG(Shader, Info, "Successfully compiled vertex shader to SPIRV!");

            const std::vector<uint32_t> Spirv{Result.begin(), Result.end()};
            m_VertexHandle = glCreateShader(GL_VERTEX_SHADER);
            glShaderBinary(1, &m_VertexHandle, GL_SHADER_BINARY_FORMAT_SPIR_V, Spirv.data(), (int32_t)(Spirv.size() * sizeof(uint32_t)));
            glSpecializeShader(m_VertexHandle, "main", 0, nullptr, nullptr);

            
            int Success = 0;
            glGetShaderiv(m_VertexHandle, GL_COMPILE_STATUS, &Success);
            if(!Success)
            {
                int32_t Length = 0;
                char Message[GL_INFO_LOG_LENGTH];
                glGetShaderInfoLog(m_VertexHandle, GL_INFO_LOG_LENGTH, &Length, Message);
                HYDRO_LOG(Shader, Error, "Failed to compiled vertex shader: {}", Message);
                return Compiled = Success;
            }
            
            //ShaderCache::CacheShaderSpirv(*this, Data, shaderc_vertex_shader);
            HYDRO_LOG(Shader, Info, "Successfully compiled vertex shader!");
        }

        // Compile Fragment
        {
            HYDRO_LOG(Shader, Trace, "Compiling fragment shader: {}", m_Filepath.string());
            const std::string ShaderID = fmt::format("{}.frag", m_Filepath.stem().string());
            const shaderc::SpvCompilationResult Result = Compiler.CompileGlslToSpv(m_Source.Vertex, shaderc_fragment_shader, ShaderID.c_str(), "main", Options);

            if (Result.GetCompilationStatus() != shaderc_compilation_status_success)
            {
                HYDRO_LOG(Shader, Error, "Fragment Shader {} failed to compile!", m_Filepath.filename().string());
                HYDRO_LOG(Shader, Error, Result.GetErrorMessage());
                return Compiled = false;
            }

            const std::vector<uint32_t> Spirv{Result.begin(), Result.end()};
            m_FragmentHandle = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderBinary(1, &m_FragmentHandle, GL_SHADER_BINARY_FORMAT_SPIR_V, Spirv.data(), (int32_t)(Spirv.size() * sizeof(uint32_t)));
            glSpecializeShader(m_FragmentHandle, "main", 0, nullptr, nullptr);

            
            int Success = 0;
            glGetShaderiv(m_FragmentHandle, GL_COMPILE_STATUS, &Success);
            if(!Success)
            {
                int32_t Length = 0;
                char Message[GL_INFO_LOG_LENGTH];
                glGetShaderInfoLog(m_FragmentHandle, GL_INFO_LOG_LENGTH, &Length, Message);
                HYDRO_LOG(Shader, Error, "Failed to compiled fragment shader: {}", Message);
                return Compiled = Success;
            }
            
            //ShaderCache::CacheShaderSpirv(*this, Data, shaderc_fragment_shader);
            HYDRO_LOG(Shader, Info, "Successfully compiled fragment shader!");
        }

        m_Program = glCreateProgram();
        glAttachShader(m_Program, m_VertexHandle);
        glAttachShader(m_Program, m_FragmentHandle);
        return Compiled = true;
    }

    bool OpenGLShader::Link()
    {
        if(!Compiled)
        {
            HYDRO_LOG(Shader, Error, "Shader program failed to link: One or more shader(s) failed to compile!");
            return Linked = false;
        }
        
        glLinkProgram(m_Program);
        int32_t Success = 0;
        glGetProgramiv(m_Program, GL_LINK_STATUS, &Success);
        if(!Success)
        {
            int32_t Length = 0;
            char Message[GL_INFO_LOG_LENGTH];
            glGetProgramInfoLog(m_Program, GL_INFO_LOG_LENGTH, &Length, Message);
            HYDRO_LOG(Shader, Error, "Shader program failed to link: {}", Message);
        }
        HYDRO_LOG(Shader, Info, "Shader program {} successfully linked!", m_Filepath.string());
        return Linked = Success;
    }

    bool OpenGLShader::Validate()
    {
        if(!Linked)
        {
            HYDRO_LOG(Shader, Error, "Shader program failed to validate: Shader program failed to link!");
            return Validated = false;
        }
        glValidateProgram(m_Program);
        int32_t Success = 0;
        glGetProgramiv(m_Program, GL_VALIDATE_STATUS, &Success);
        if(!Success)
        {
            int32_t Length = 0;
            char Message[GL_INFO_LOG_LENGTH];
            glGetProgramInfoLog(m_Program, GL_INFO_LOG_LENGTH, &Length, Message);
            HYDRO_LOG(Shader, Error, "Shader program failed to validate: {}", Message);
        }
        HYDRO_LOG(Shader, Info, "Shader program {} successfully validated!", m_Filepath.string());
        return Validated = Success;
    }

    bool OpenGLShader::UseProgram()
    {
        if(!Validated)
        {
            HYDRO_LOG(Shader, Error, "Cannot use this shader: Not a valid shader!");
            return false;
        }

        glUseProgram(m_Program);
        return true;
    }

    uint32_t OpenGLShader::ShadercToOpenGL(shaderc_shader_kind Kind)
    {
        switch (Kind)
        {
        case shaderc_vertex_shader: return GL_VERTEX_SHADER;
        case shaderc_fragment_shader: return GL_FRAGMENT_SHADER;
        case shaderc_geometry_shader: return GL_GEOMETRY_SHADER;
        case shaderc_compute_shader: return GL_COMPUTE_SHADER;
        default: return GL_NONE;
        }
    }

    shaderc_shader_kind OpenGLShader::OpenGLToShaderc(uint32_t Type)
    {
        switch (Type)
        {
        case GL_VERTEX_SHADER: return shaderc_vertex_shader;
        case GL_FRAGMENT_SHADER: return shaderc_fragment_shader;
        case GL_GEOMETRY_SHADER: return shaderc_geometry_shader;
        case GL_COMPUTE_SHADER: return shaderc_compute_shader;
        default: HYDRO_ASSERT(false, "Bad OpenGL shader type value");
        }
        HYDRO_ASSERT(false, "Bad OpenGL shader type value");
        return (shaderc_shader_kind)0;
    }
}
