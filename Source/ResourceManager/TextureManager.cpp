#include "HydroPCH.h"
#include "TextureManager.h"

#include "Core/Log.h"
#include "Core/LogVerbosity.h"
#include "Core/Texture2D.h"

namespace Hydro
{
    Ref<Texture2D> TextureManager::Load(const std::string& Name, const Path& Filepath)
    {
        Ref<Texture2D> LoadedTexture = Texture2D::CreateFromFile(Name, Filepath);
        if(!LoadedTexture) return nullptr;
        m_Data[Name] = LoadedTexture;
        return LoadedTexture;
    }

    Ref<Texture2D> TextureManager::Retrieve(const std::string& Name)
    {
        if(!m_Data.contains(Name))
        {
            HYDRO_LOG(TextureManager, Verbosity::Warning, "Texture \"{}\" not found!", Name);
            return nullptr;
        }
        return m_Data[Name];
    }
}
