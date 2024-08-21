#include "HydroPCH.h"
#include "TextureManager.h"

#include "Core/Log.h"
#include "Core/LogVerbosity.h"
#include "Core/Texture2D.h"

namespace Hydro
{
    Ref<Texture2D> TextureManager::Load(const String& Name, const Path& Filepath)
    {
        constexpr TextureParams DefaultParams = {
            .Filter = TextureFilter::Nearest,
            .Wrap = TextureWrap::Repeat,
        };
        
        Ref<Texture2D> LoadedTexture = Texture2D::CreateFromFile(*Name, Filepath, DefaultParams);
        if(!LoadedTexture) return nullptr;
        m_Data[Name] = LoadedTexture;
        return LoadedTexture;
    }

    Ref<Texture2D> TextureManager::Load(const String& Name, const Path& Filepath, const TextureParams& Params)
    {
        Ref<Texture2D> LoadedTexture = Texture2D::CreateFromFile(*Name, Filepath, Params);
        if(!LoadedTexture) return nullptr;
        m_Data[Name] = LoadedTexture;
        return LoadedTexture;
    }

    Ref<Texture2D> TextureManager::Retrieve(const String& Name)
    {
        if(!m_Data.Contains(Name))
        {
            HYDRO_LOG(TextureManager, Verbosity::Warning, "Texture \"{}\" not found!", Name);
            return nullptr;
        }
        return m_Data[Name];
    }
}
