#include "HydroPCH.h"
#include "VulkanShader.h"
#include "Core/ShaderUtils.h"
#include <shaderc/shaderc.hpp>

#include "VulkanRenderer.h"
#include "Core/Application.h"
#include "Core/Assertion.h"
#include "Core/Log.h"
#include "Core/LogVerbosity.h"
#include "Core/Renderer.h"

namespace Hydro
{
    VulkanShader::VulkanShader(const std::string& Name, const Path& Filepath, ShaderSourceLanguage Language) : Shader(Name, Filepath, Language)
    {
        const shaderc::CompileOptions Options = ShaderUtils::CreateShadercCompileOptions(m_SourceLanguage);
        const shaderc::Compiler Compiler;
        HYDRO_ASSERT(Compiler.IsValid(), "shaderc compiler is not valid!");
    }

    VulkanShader::VulkanShader(const std::string& Name, const Buffer<uint8_t>& Buffer, ShaderSourceLanguage Language) : Shader(Name, Buffer, Language)
    {
        const shaderc::CompileOptions Options = ShaderUtils::CreateShadercCompileOptions(m_SourceLanguage);
        const shaderc::Compiler Compiler;
        HYDRO_ASSERT(Compiler.IsValid(), "shaderc compiler is not valid!");

        const std::string Source((const char*)Buffer.GetData(), Buffer.Count());
        SplitSources(Source);
        
        const auto Result = Compiler.CompileGlslToSpv(m_Source.Vertex, shaderc_shader_kind::shaderc_vertex_shader, Name.c_str(), "main", Options);
        if(Result.GetCompilationStatus() != shaderc_compilation_status_success)
        {
            HYDRO_LOG(Shader, Error, "Vertex shader {} failed to compile: {}.", Name, Result.GetErrorMessage());
            
        }
    }

    VulkanShader::VulkanShader(const std::string& Name, const ShaderSource& ShaderSource, ShaderSourceLanguage Language)
        : Shader(Name, ShaderSource, Language)
    {
    }

    bool VulkanShader::Compile()
    {
        return false;
    }

    bool VulkanShader::Link()
    {
        return false;
    }

    bool VulkanShader::Validate()
    {
        return false;
    }

    bool VulkanShader::Bind()
    {
        return false;
    }

    void VulkanShader::Delete()
    {
    }

    void VulkanShader::SetUniformFloat(const std::string& Name, float Value)
    {
        Shader::SetUniformFloat(Name, Value);
    }

    void VulkanShader::SetUniformFloat2(const std::string& Name, const glm::vec2& Value)
    {
        Shader::SetUniformFloat2(Name, Value);
    }

    void VulkanShader::SetUniformFloat3(const std::string& Name, const glm::vec3& Value)
    {
        Shader::SetUniformFloat3(Name, Value);
    }

    void VulkanShader::SetUniformFloat4(const std::string& Name, const glm::vec4& Value)
    {
        Shader::SetUniformFloat4(Name, Value);
    }

    void VulkanShader::SetUniformMat4(const std::string& Name, const glm::mat4& Value)
    {
        Shader::SetUniformMat4(Name, Value);
    }

    void VulkanShader::SetUniformInt(const std::string& Name, int32_t Value)
    {
        Shader::SetUniformInt(Name, Value);
    }

    void VulkanShader::SetUniformBuffer(const std::string& Name, const void* Buffer, size_t BufferSize)
    {
        Shader::SetUniformBuffer(Name, Buffer, BufferSize);
    }

    void VulkanShader::SetUniformTexture(const std::string& Name, const Ref<Texture2D>& Texture)
    {
        Shader::SetUniformTexture(Name, Texture);
    }

    float VulkanShader::GetUniformFloat(const std::string& Name)
    {
        return Shader::GetUniformFloat(Name);
    }

    glm::vec2 VulkanShader::GetUniformFloat2(const std::string& Name)
    {
        return Shader::GetUniformFloat2(Name);
    }

    glm::vec3 VulkanShader::GetUniformFloat3(const std::string& Name)
    {
        return Shader::GetUniformFloat3(Name);
    }

    glm::vec4 VulkanShader::GetUniformFloat4(const std::string& Name)
    {
        return Shader::GetUniformFloat4(Name);
    }

    glm::mat4 VulkanShader::GetUniformMat4(const std::string& Name)
    {
        return Shader::GetUniformMat4(Name);
    }

    int32_t VulkanShader::GetUniformInt(const std::string& Name)
    {
        return Shader::GetUniformInt(Name);
    }
}
