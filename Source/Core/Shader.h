#pragma once
#include "Core/Filesystem.h"
#include "SharedPointer.h"
#include "Core/ShaderSource.h"
#include "Core/ShaderSourceLanguage.h"
#include "Core/LogCategory.h"
#include "Math/LinearAlgebra.h"
#include <string>

HYDRO_DECLARE_LOG_CATEGORY_STATIC(Shader, "SHADER");

namespace Hydro
{
    class Texture2D;

    class Shader
    {
    public:
        virtual ~Shader() = default;

        virtual bool Reload()
        {
            Bind();
            Delete();
            LoadSource(m_Filepath, m_SourceLanguage);
            bool Result = Compile();
            if(!Result) return false;

            Result = Link();
            if(!Result) return false;

            Result = Validate();
            if(!Result) return false;
            return true;
        }
        virtual bool Compile() = 0;
        virtual bool Link() = 0;
        virtual bool Validate() = 0;
        virtual bool Bind() = 0;
        virtual void Delete() = 0;
        
        virtual void SetUniformFloat(const std::string& Name, f32 Value){}
        virtual void SetUniformFloat2(const std::string& Name, const Vector2& Value){}
        virtual void SetUniformFloat3(const std::string& Name, const Vector3& Value){}
        virtual void SetUniformFloat4(const std::string& Name, const Vector4& Value){}
        virtual void SetUniformMat4(const std::string& Name, const Matrix4& Value){}
        virtual void SetUniformInt(const std::string& Name, i32 Value){}
        virtual void SetUniformTexture(const std::string& Name, const Ref<Texture2D>& Texture){}
        virtual void SetUniformMat2(const std::string& Name, const Matrix2& Value){}
        virtual void SetUniformMat3(const std::string& Name, const Matrix3& Value){}

        virtual f32 GetUniformFloat(const std::string& Name){ return 0.0f; }
        virtual Vector2 GetUniformFloat2(const std::string& Name){ return Vector2::Zero; }
        virtual Vector3 GetUniformFloat3(const std::string& Name){ return Vector3::Zero; }
        virtual Vector4 GetUniformFloat4(const std::string& Name){ return Vector4::Zero; }
        virtual Matrix4 GetUniformMat4(const std::string& Name){ return Matrix4::Identity; }
        virtual i32 GetUniformInt(const std::string& Name){ return 0;}
        
        std::string GetFilename() const;
        

        static Ref<Shader> Create(const std::string& Name, const Path& Filepath, ShaderSourceLanguage Language);
        static Ref<Shader> Create(const std::string& Name, const Buffer<u8>& Buffer, ShaderSourceLanguage Language);
        static Ref<Shader> Create(const std::string& Name, const ShaderSource& ShaderSource, ShaderSourceLanguage Language);
    

        
    protected:
        explicit Shader(std::string Name, Path Filepath, ShaderSourceLanguage Language);
        explicit Shader(std::string Name, const Buffer<u8>& Buffer, ShaderSourceLanguage Language);
        explicit Shader(std::string Name, const ShaderSource& ShaderSource, ShaderSourceLanguage Language);
        std::string m_Name;
        Path m_Filepath;
        ShaderSource m_Source;
        ShaderSourceLanguage m_SourceLanguage;

        bool Compiled{false};
        bool Linked{false};
        bool Validated{false};

        void LoadSource(Path Filepath, ShaderSourceLanguage Language);
        void SplitSources(const std::string& Source);
        bool Preprocess(std::string& Source);
        std::string GetName();
    };


    
}
