#pragma once
#include "Core/Component.h"

HYDRO_DECLARE_LOG_CATEGORY_STATIC(SoundEmitter, "SOUND EMITTER")

namespace FMOD
{
    class System;
    class Channel;
}

namespace Hydro
{
    class Sound;

    class SoundEmitter : public Component
    {
    public:
        using EmitterStartedDelegate = MulticastDelegate<void(Ref<Sound> Sound, bool WasPaused)>;
        using EmitterStopDelegate = MulticastDelegate<void(Ref<Sound> Sound, bool IsPause)>;
        using EmitterPlayingDelegate = MulticastDelegate<void(Ref<Sound> Sound, uint32_t Position, uint32_t Length)>;
        
        SoundEmitter(GameObject* Owner);

        void OnInit() override;
        void OnUpdate(float Delta) override;
        void OnInspectorGUI(const ImGuiIO& IO) override;
        void OnDestroy() override;

        void Play();
        void Stop();
        bool IsPlaying() const;
        void Pause();
        void Resume();

        void SetSound(const Ref<Sound>& Clip);
        void SetVolume(float Vol);
        void SetPitch(float Pitch);
        float GetVolume() const;
        float GetPitch() const;

        EmitterStartedDelegate OnStartedEvent;
        EmitterStopDelegate OnStopEvent;
        EmitterPlayingDelegate OnPlayingEvent;
    
        void OnPlaying(Ref<Sound> Sound, uint32_t Position, uint32_t Length);
    private:
        Ref<Sound> m_Sound = nullptr;
        float m_Volume = 1.0f;
        float m_Pitch = 1.0f;
        bool m_Looping = false;
        uint32_t m_PlaybackPosition;
        uint32_t m_Length;
        
        FMOD::System* m_System = nullptr;
        FMOD::Channel* m_Channel = nullptr;

        
    };
}
