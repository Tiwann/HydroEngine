#pragma once
#include "SoundFormat.h"
#include "SoundType.h"
#include "Core/Filesystem.h"
#include "Core/SharedPointer.h"
#include "Audio/SoundOptions.h"
#include "Core/GUID.h"

HYDRO_DECLARE_LOG_CATEGORY_STATIC(AudioClip, "AUDIO CLIP")

namespace FMOD
{
    class Sound;
}

namespace Hydro
{
    class Sound
    {
    public:
        Sound();
        ~Sound();
        

        static Ref<Sound> CreateFromFile(const Path& Filepath, SoundFlags Flags);

        bool LoadData(const Path& Filepath, SoundFlags Flags);
        GUID GetGuid() const;
        FMOD::Sound* GetHandle() const;
        SoundFlags GetFlags() const;
        
        void SetFlags(SoundFlags Flags);
        SoundType GetType() const;
        SoundFormat GetFormat() const;
        uint32_t GetChannels() const;
        uint32_t GetBitsPerSample() const;
        float GetDuration() const;
    private:
        friend class AudioSystem;

        GUID m_Guid;
        FMOD::Sound* m_Handle = nullptr;
        SoundFlags m_Flags;
        SoundType m_Type;
        SoundFormat m_Format;
        uint32_t m_Channels;
        uint32_t m_BitsPerSample;
        float m_Duration;
    };
}
