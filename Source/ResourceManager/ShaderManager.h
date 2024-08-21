#pragma once
#include "ResourceManager.h"
#include "Core/Shader.h"
#include "Core/LogCategory.h"

HYDRO_DECLARE_LOG_CATEGORY_STATIC(ShaderManager, "SHADER MANAGER")

namespace Hydro
{
    class ShaderManager : public ResourceManager<Shader>
    {
    public:
        ShaderManager() = default;
        
        Ref<Shader> Load(const String& Name, const Path& Filepath) override;
        Ref<Shader> Retrieve(const String& Name) override;
        void ReloadAll();
    };
}
