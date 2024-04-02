#pragma once
#include "Core/Shader.h"

namespace Hydro
{
    class VulkanShader : public Shader
    {
    public:
        VulkanShader(const std::string& Name, const Path& Filepath, ShaderSourceLanguage Language);
        VulkanShader(const std::string& Name, const Buffer<uint8_t>& Buffer, ShaderSourceLanguage Language);
        VulkanShader(const std::string& Name, const ShaderSource& ShaderSource, ShaderSourceLanguage Language);

        /* Shader Implementation */
        bool Compile() override;
        bool Link() override;
        bool Validate() override;
        bool Bind() override;
        void Delete() override;
        void SetUniformFloat(const std::string& Name, float Value) override;
        void SetUniformFloat2(const std::string& Name, const glm::vec2& Value) override;
        void SetUniformFloat3(const std::string& Name, const glm::vec3& Value) override;
        void SetUniformFloat4(const std::string& Name, const glm::vec4& Value) override;
        void SetUniformMat4(const std::string& Name, const glm::mat4& Value) override;
        void SetUniformInt(const std::string& Name, int32_t Value) override;
        void SetUniformBuffer(const std::string& Name, const void* Buffer, size_t BufferSize) override;
        void SetUniformTexture(const std::string& Name, const Ref<Texture2D>& Texture) override;
        float GetUniformFloat(const std::string& Name) override;
        glm::vec2 GetUniformFloat2(const std::string& Name) override;
        glm::vec3 GetUniformFloat3(const std::string& Name) override;
        glm::vec4 GetUniformFloat4(const std::string& Name) override;
        glm::mat4 GetUniformMat4(const std::string& Name) override;
        int32_t GetUniformInt(const std::string& Name) override;
    };
}
