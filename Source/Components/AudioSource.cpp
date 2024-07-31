#include "HydroPCH.h"
#include "AudioSource.h"
#include <miniaudio/miniaudio.h>

#include "Transform.h"
#include "Physics/PhysicsComponent.h"

namespace Hydro
{
    AudioSource::AudioSource(GameObject* Owner): Component(Owner, AudioSourceComponentName)
    {
        
    }

    void AudioSource::OnInit()
    {
        Component::OnInit();
        
    }

    void AudioSource::OnUpdate(float Delta)
    {
        Component::OnUpdate(Delta);
        const Vector3 Position = GetTransform()->GetPosition();
        ma_engine_listener_set_position(nullptr, 0, Position.x, Position.y, Position.z);
        if(const auto& Physics = m_GameObject->GetComponent<PhysicsComponent>())
        {
            Vector3 Velocity = Physics->GetLinearVelocity();
            ma_engine_listener_set_velocity(nullptr, 0, Velocity.x, Velocity.y, Velocity.z);
        }
    }

    void AudioSource::OnDestroy()
    {
        Component::OnDestroy();
    }

    void AudioSource::Play()
    {
    }

    void AudioSource::PlayScheduled(float Delay)
    {
    }

    void AudioSource::SetClip(const Ref<AudioClip>& Clip)
    {
        m_Clip = Clip;
    }

    void AudioSource::SetVolume(float Vol)
    {
        m_Volume = Vol;
    }

    void AudioSource::SetPitch(float Pitch)
    {
        m_Pitch = Pitch;
    }

    float AudioSource::GetVolume() const
    {
        return m_Volume;
    }

    float AudioSource::GetPitch() const
    {
        return m_Pitch;
    }
}
