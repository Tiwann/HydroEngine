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
    class AudioEngine
    {
    public:
        AudioEngine() = default;
        ~AudioEngine();
        static Ref<AudioEngine> Create();

        bool Init(uint32_t SampleRate, uint32_t CallbackBufferSize);
        void Destroy();
        void OnUpdate();

        FMOD::Sound* CreateSound(const Path& Filepath, SoundFlags Flags);
        FMOD::System* GetSystem() const;

    private:
        FMOD::System* m_System = nullptr;
    };
}
