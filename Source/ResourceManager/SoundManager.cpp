#include "HydroPCH.h"
#include "SoundManager.h"
#include "Core/Application.h"
#include "Audio/AudioEngine.h"


namespace Hydro
{
    Ref<Sound> SoundManager::Load(const std::string& Name, const Path& Filepath, SoundFlags Flags)
    {
        Ref<Sound> LoadedSound = Load(Name, Filepath);
        if(!LoadedSound) return nullptr;
        LoadedSound->SetFlags(Flags);
        return LoadedSound;
    }

    Ref<Sound> SoundManager::Load(const std::string& Name, const Path& Filepath)
    {
        Ref<Sound> LoadedSound = Sound::CreateFromFile(Filepath, SoundFlagBits::Default);
        m_Data[Name] = LoadedSound;
        return LoadedSound;
    }

    Ref<Sound> SoundManager::Retrieve(const std::string& Name)
    {
        if(!m_Data.contains(Name))
        {
            HYDRO_LOG(SoundManager, Verbosity::Warning, "Sound \"{}\" not found!", Name);
            return nullptr;
        }
        return m_Data[Name];
    }
}
