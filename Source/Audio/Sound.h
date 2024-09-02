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
        u32 GetChannels() const;
        u32 GetBitsPerSample() const;
        f32 GetDuration() const;
    private:
        friend class AudioSystem;

        GUID m_Guid;
        FMOD::Sound* m_Handle = nullptr;
        SoundFlags m_Flags;
        SoundType m_Type;
        SoundFormat m_Format;
        u32 m_Channels;
        u32 m_BitsPerSample;
        f32 m_Duration;
    };
}
