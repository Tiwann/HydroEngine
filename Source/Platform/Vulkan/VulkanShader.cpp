#include "HydroPCH.h"
#include "VulkanShader.h"
#include "Core/Application.h"
#include "Core/Assertion.h"
#include "Core/Log.h"
#include "Core/LogVerbosity.h"

namespace Hydro
{
    VulkanShader::VulkanShader(const std::string& Name, const Path& Filepath, ShaderSourceLanguage Language) : Shader(Name, Filepath, Language)
    {
        
    }

    VulkanShader::VulkanShader(const std::string& Name, const Buffer<uint8_t>& Buffer, ShaderSourceLanguage Language) : Shader(Name, Buffer, Language)
    {
        
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

    void VulkanShader::SetUniformFloat2(const std::string& Name, const Vector2& Value)
    {
        Shader::SetUniformFloat2(Name, Value);
    }

    void VulkanShader::SetUniformFloat3(const std::string& Name, const Vector3& Value)
    {
        Shader::SetUniformFloat3(Name, Value);
    }

    void VulkanShader::SetUniformFloat4(const std::string& Name, const Vector4& Value)
    {
        Shader::SetUniformFloat4(Name, Value);
    }

    void VulkanShader::SetUniformMat4(const std::string& Name, const Matrix4& Value)
    {
        Shader::SetUniformMat4(Name, Value);
    }

    void VulkanShader::SetUniformMat2(const std::string& Name, const Matrix2& Value)
    {
        Shader::SetUniformMat2(Name, Value);
    }

    void VulkanShader::SetUniformMat3(const std::string& Name, const Matrix3& Value)
    {
        Shader::SetUniformMat3(Name, Value);
    }

    void VulkanShader::SetUniformInt(const std::string& Name, int32_t Value)
    {
        Shader::SetUniformInt(Name, Value);
    }

    void VulkanShader::SetUniformTexture(const std::string& Name, const Ref<Texture2D>& Texture)
    {
        Shader::SetUniformTexture(Name, Texture);
    }

    float VulkanShader::GetUniformFloat(const std::string& Name)
    {
        return Shader::GetUniformFloat(Name);
    }

    int32_t VulkanShader::GetUniformInt(const std::string& Name)
    {
        return Shader::GetUniformInt(Name);
    }

    Vector2 VulkanShader::GetUniformFloat2(const std::string& Name)
    {
        return Shader::GetUniformFloat2(Name);
    }

    Vector3 VulkanShader::GetUniformFloat3(const std::string& Name)
    {
        return Shader::GetUniformFloat3(Name);
    }

    Vector4 VulkanShader::GetUniformFloat4(const std::string& Name)
    {
        return Shader::GetUniformFloat4(Name);
    }

    Matrix4 VulkanShader::GetUniformMat4(const std::string& Name)
    {
        return Shader::GetUniformMat4(Name);
    }
}
