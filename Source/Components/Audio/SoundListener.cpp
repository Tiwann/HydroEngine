#include "SoundListener.h"

#include "Core/Application.h"
#include "Audio/AudioEngine.h"
#include "Components/Transform.h"
#include "Components/Physics/PhysicsComponent.h"
#include <fmod/fmod.hpp>

#include "Editor/EditorGUI.h"

static constexpr char ComponentName[14] = "Sound Litener";

namespace Hydro
{
    SoundListener::SoundListener(Entity* Owner): Component(Owner, ComponentName)
    {
        
    }

    void SoundListener::OnInit()
    {
        Component::OnInit();
        const Ref<AudioEngine>& Engine = g_Application->GetAudioEngine();
        m_System = Engine->GetSystem();
    }

    void SoundListener::OnDestroy()
    {
        Component::OnDestroy();
        m_System = nullptr;
    }

    void SoundListener::OnStart()
    {
        Component::OnStart();
    }

    void SoundListener::OnUpdate(float Delta)
    {
        Component::OnUpdate(Delta);

        const Ref<PhysicsComponent>& Physics = m_Entity->GetComponent<PhysicsComponent>();
        const Vector3 Position = GetTransform()->GetPosition();
        const Vector3 Forward = GetTransform()->GetForwardVector();
        const Vector3 Up = GetTransform()->GetUpVector();
        const Vector3 Velocity = Physics ? Physics->GetLinearVelocity() : Vector3::Zero;
        
        m_System->set3DListenerAttributes((int)m_Index,
            (const FMOD_VECTOR*)&Position,
            (const FMOD_VECTOR*)&Velocity,
            (const FMOD_VECTOR*)&Forward,
            (const FMOD_VECTOR*)&Up);

        
    }

    void SoundListener::OnInspectorGUI(const ImGuiIO& IO)
    {
        Component::OnInspectorGUI(IO);
        UI::SliderValue<uint32_t>("Index", m_Index, 0, FMOD_MAX_LISTENERS, "%d", SliderFlagBits::AlwaysClamp);
    }

    void SoundListener::SetIndex(uint32_t Index)
    {
        m_Index = Index;
    }
    
}
