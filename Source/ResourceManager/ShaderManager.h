#pragma once
#include "ResourceManager.h"
#include "Core/Shader.h"

HYDRO_DECLARE_LOG_CATEGORY_STATIC(ShaderManager, "SHADER MANAGER")

namespace Hydro
{
    class ShaderManager : public ResourceManager<Shader>
    {
    public:
        ShaderManager() = default;
        
        Ref<Shader> Load(const std::string& Name, const Path& Filepath) override;
        Ref<Shader> Retrieve(const std::string& Name) override;
        void ReloadAll();
    };
}
