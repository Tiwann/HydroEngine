#pragma once
#include "Core/Component.h"

namespace Hydro
{
    class AudioClip;

    class AudioSource : public Component
    {
    public:
        static constexpr std::string AudioSourceComponentName = "Audio Source";
        AudioSource(GameObject* Owner);

        void OnInit() override;
        void OnUpdate(float Delta) override;
        void OnDestroy() override;

        void Play();
        void PlayScheduled(float Delay);
        void SetClip(const Ref<AudioClip>& Clip);

        void SetVolume(float Vol);
        void SetPitch(float Pitch);

        float GetVolume() const;
        float GetPitch() const;

    private:
        Ref<AudioClip> m_Clip;
        float m_Volume = 1.0f;
        float m_Pitch = 1.0f;
        
    };
}
