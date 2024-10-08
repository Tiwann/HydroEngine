﻿#pragma once
#include "Core/Shader.h"
#include "Core/ShaderSourceLanguage.h"

namespace Hydro
{
    class OpenGLShader : public Shader
    {
    public:
        explicit OpenGLShader(const std::string& Name, Path Filepath, ShaderSourceLanguage Language);
        explicit OpenGLShader(const std::string& Name, Buffer<u8> Buffer, ShaderSourceLanguage Language);
        explicit OpenGLShader(const std::string& Name, const ShaderSource& ShaderSource, ShaderSourceLanguage Language);
        ~OpenGLShader() override;
        bool Compile() override;
        bool Link() override;
        bool Validate() override;
        bool Bind() override;
        void Delete() override;
        
        
        void SetUniformFloat(const std::string& Name, f32 Value) override;
        void SetUniformFloat2(const std::string& Name, const Vector2& Value) override;
        void SetUniformFloat3(const std::string& Name, const Vector3& Value) override;
        void SetUniformFloat4(const std::string& Name, const Vector4& Value) override;
        void SetUniformInt(const std::string& Name, i32 Value) override;
        void SetUniformTexture(const std::string& Name, const Ref<Texture2D>& Texture) override;
        void SetUniformMat2(const std::string& Name, const Matrix2& Value) override;
        void SetUniformMat3(const std::string& Name, const Matrix3& Value) override;
        void SetUniformMat4(const std::string& Name, const Matrix4& Value) override;

        f32 GetUniformFloat(const std::string& Name) override;
        Vector2 GetUniformFloat2(const std::string& Name) override;
        Vector3 GetUniformFloat3(const std::string& Name) override;
        Vector4 GetUniformFloat4(const std::string& Name) override;
        Matrix4 GetUniformMat4(const std::string& Name) override;
        i32 GetUniformInt(const std::string& Name) override;
        
    protected:
        u32 m_Program;
        u32 m_VertexHandle;
        u32 m_FragmentHandle;

    private:
        bool CompileOpenGL();
    };
}
