#pragma once
#include "ResourceManager.h"
#include "Core/Texture2D.h"

HYDRO_DECLARE_LOG_CATEGORY_STATIC(TextureManager, "TEXTURE MANAGER")

namespace Hydro
{
    class TextureManager : public ResourceManager<Texture2D>
    {
    public:
        TextureManager() = default;
        
        Ref<Texture2D> Load(const String& Name, const Path& Filepath) override;
        Ref<Texture2D> Load(const String& Name, const Path& Filepath, const TextureParams& Params);
        Ref<Texture2D> Retrieve(const String& Name) override;
    };

    
}
