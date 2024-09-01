#pragma once
#include "Core/Shader.h"

namespace Hydro
{
    class VulkanShader : public Shader
    {
    public:
        VulkanShader(const std::string& Name, const Path& Filepath, ShaderSourceLanguage Language);
        VulkanShader(const std::string& Name, const Buffer<uint8>& Buffer, ShaderSourceLanguage Language);
        VulkanShader(const std::string& Name, const ShaderSource& ShaderSource, ShaderSourceLanguage Language);
        
        bool Compile() override;
        bool Link() override;
        bool Validate() override;
        bool Bind() override;
        void Delete() override;
        void SetUniformFloat(const std::string& Name, float Value) override;
        void SetUniformFloat2(const std::string& Name, const Vector2& Value) override;
        void SetUniformFloat3(const std::string& Name, const Vector3& Value) override;
        void SetUniformFloat4(const std::string& Name, const Vector4& Value) override;
        void SetUniformMat4(const std::string& Name, const Matrix4& Value) override;
        void SetUniformMat2(const std::string& Name, const Matrix2& Value) override;
        void SetUniformMat3(const std::string& Name, const Matrix3& Value) override;
        void SetUniformInt(const std::string& Name, int32 Value) override;
        void SetUniformTexture(const std::string& Name, const Ref<Texture2D>& Texture) override;

        float GetUniformFloat(const std::string& Name) override;
        int32 GetUniformInt(const std::string& Name) override;
        Vector2 GetUniformFloat2(const std::string& Name) override;
        Vector3 GetUniformFloat3(const std::string& Name) override;
        Vector4 GetUniformFloat4(const std::string& Name) override;
        Matrix4 GetUniformMat4(const std::string& Name) override;

        vk::Pipeline GetPipeline() const { return m_Pipeline; }
        vk::ShaderModule GetVertexModule() const { return m_VertexModule; }
        vk::ShaderModule GetFragmentModule() const { return m_FragmentModule; }
        
    private:
        vk::Pipeline m_Pipeline;
        vk::ShaderModule m_VertexModule;
        vk::ShaderModule m_FragmentModule;
    };
}
