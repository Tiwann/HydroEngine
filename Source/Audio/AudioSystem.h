#pragma once
#include "SoundOptions.h"
#include "Core/Filesystem.h"
#include "Core/LogCategory.h"
#include "Core/SharedPointer.h"

HYDRO_DECLARE_LOG_CATEGORY_STATIC(AudioEngine, "AUDIO ENGINE")
HYDRO_DECLARE_LOG_CATEGORY_STATIC(FMOD, "FMOD")

namespace FMOD
{
    class System;
    class Sound;
}

namespace Hydro
{
    class AudioSystem
    {
    public:
        AudioSystem() = default;
        ~AudioSystem() = default;

        bool Init(u32 SampleRate, u32 CallbackBufferSize);
        void Destroy();
        void OnUpdate();

        FMOD::Sound* CreateSound(const Path& Filepath, SoundFlags Flags);
        FMOD::System* GetHandle() const;

    private:
        FMOD::System* m_Handle = nullptr;
    };
}
