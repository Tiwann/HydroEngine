#include "SoundManager.h"
#include "Core/Application.h"
#include "Audio/AudioSystem.h"


namespace Hydro
{
    Ref<Sound> SoundManager::Load(const String& Name, const Path& Filepath, SoundFlags Flags)
    {
        Ref<Sound> LoadedSound = Load(Name, Filepath);
        if(!LoadedSound) return nullptr;
        LoadedSound->SetFlags(Flags);
        return LoadedSound;
    }

    Ref<Sound> SoundManager::Load(const String& Name, const Path& Filepath)
    {
        Ref<Sound> LoadedSound = Sound::CreateFromFile(Filepath, SoundFlagBits::Default);
        m_Data[Name] = LoadedSound;
        return LoadedSound;
    }

    Ref<Sound> SoundManager::Retrieve(const String& Name)
    {
        if(!m_Data.Contains(Name))
        {
            HYDRO_LOG(SoundManager, Verbosity::Warning, "Sound \"{}\" not found!", Name);
            return nullptr;
        }
        return m_Data[Name];
    }
}
