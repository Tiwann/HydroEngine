#include "Sound.h"
#include "AudioSystem.h"
#include "Core/Application.h"

#include <fmod/fmod.hpp>


namespace Hydro
{
    Sound::Sound()
    : m_Flags(SoundFlagBits::Default),
    m_Type(SoundType::UNKNOWN),
    m_Format(SoundFormat::None),
    m_Channels(0),
    m_BitsPerSample(0),
    m_Duration(0)
    {
    }

    Sound::~Sound()
    {
        m_Handle->release();
    }

    Ref<Sound> Sound::CreateFromFile(const Path& Filepath, SoundFlags Flags)
    {
        Ref<Sound> NewSound = CreateRef<Sound>();
        if(!NewSound->LoadData(Filepath, Flags))
        {
            NewSound.reset();
            return nullptr;
        }
        return NewSound;
    }

    bool Sound::LoadData(const Path& Filepath, SoundFlags Flags)
    {
        m_Flags = Flags;
        AudioSystem& AudioSystem = g_Application->GetAudioSystem();
        FMOD::Sound* LoadedSound = AudioSystem.CreateSound(Filepath, Flags);
        if(!LoadedSound) return false;
        m_Handle = LoadedSound;
        
        m_Handle->getFormat((FMOD_SOUND_TYPE*)&m_Type,
            (FMOD_SOUND_FORMAT*)&m_Format,
            (int*)&m_Channels,
            (int*)&m_BitsPerSample);

        uint32_t Length;
        m_Handle->getLength(&Length, FMOD_TIMEUNIT_MS);
        m_Duration = (float)Length / 1000.0f;
        
        return true;
    }

    GUID Sound::GetGuid() const
    {
        return m_Guid;
    }

    FMOD::Sound* Sound::GetHandle() const
    {
        return m_Handle;
    }

    SoundFlags Sound::GetFlags() const
    {
        return m_Flags;
    }

    void Sound::SetFlags(SoundFlags Flags)
    {
        m_Handle->setMode(Flags.As<FMOD_MODE>());
        m_Flags = Flags;
    }

    SoundType Sound::GetType() const
    {
        return m_Type;
    }

    SoundFormat Sound::GetFormat() const
    {
        return m_Format;
    }

    uint32_t Sound::GetChannels() const
    {
        return m_Channels;
    }

    uint32_t Sound::GetBitsPerSample() const
    {
        return m_BitsPerSample;
    }

    float Sound::GetDuration() const
    {
        return m_Duration;
    }
}
