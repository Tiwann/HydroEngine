#include "SoundEmitter.h"
#include "Components/Transform.h"
#include "Audio/AudioSystem.h"
#include "Audio/Sound.h"
#include "Core/Application.h"
#include "Core/PopupMessage.h"
#include "Components/Physics/PhysicsComponent.h"
#include "Editor/EditorGUI.h"
#include "Core/Containers/String.h"
#include "Core/Containers/StringFormat.h"

#include <fmod/fmod.hpp>
#include <miniaudio/miniaudio.h>


static constexpr char ComponentName[14] = "Sound Emitter";

namespace Hydro
{
    
    SoundEmitter::SoundEmitter(Entity* Owner) : Component(Owner, ComponentName)
    {
        
    }

    void SoundEmitter::OnInit()
    {
        Component::OnInit();
        HYDRO_BIND_EVENT(OnPlayingEvent, &SoundEmitter::OnPlaying);
    }

    void SoundEmitter::OnDestroy()
    {
        Component::OnDestroy();
        Stop();
        m_Channel = nullptr;
        OnStartedEvent.ClearAll();
        OnStopEvent.ClearAll();
        OnPlayingEvent.ClearAll();
    }

    void SoundEmitter::OnUpdate(f32 Delta)
    {
        Component::OnUpdate(Delta);
        if(m_Channel)
        {
            {
                const Vector3 Position = GetTransform()->GetPosition();
                const auto& Physics = m_Entity->GetComponent<PhysicsComponent>();
                const Vector3 Velocity = Physics ? Physics->GetLinearVelocity() : Vector3::Zero;
                m_Channel->set3DAttributes((const FMOD_VECTOR*)&Position, (const FMOD_VECTOR*)&Velocity);
            }
            
            m_Channel->setVolume(m_Volume);
            m_Channel->setPitch(m_Pitch);

            if(m_Sound)
            {
                if(m_Looping)
                {
                    SoundFlags Flags = m_Sound->GetFlags();
                    Flags.Remove(SoundFlagBits::LoopOff);
                    Flags.Append(SoundFlagBits::LoopOn);
                    m_Channel->setMode(Flags.As<FMOD_MODE>());
                } else
                {
                    SoundFlags Flags = m_Sound->GetFlags();
                    Flags.Append(SoundFlagBits::LoopOff);
                    Flags.Remove(SoundFlagBits::LoopOn);
                    m_Channel->setMode(Flags.As<FMOD_MODE>());
                }
            }

            if(m_Sound)
            {
                u32 Position, Length;
                m_Channel->getPosition(&Position, FMOD_TIMEUNIT_PCM);
                m_Sound->GetHandle()->getLength(&Length, FMOD_TIMEUNIT_PCM);
                if(IsPlaying())
                {
                    OnPlayingEvent.Broadcast(m_Sound, Position, Length);
                }
            }
        }
        
    }

    void SoundEmitter::OnInspectorGUI(const ImGuiIO& IO)
    {
        Component::OnInspectorGUI(IO);

        if (ImGui::TreeNode("Sound"))
        {
            const String GUID = m_Sound ? m_Sound->GetGuid().GetString() : "None";
            UI::Text(Format("GUID: {}", GUID));
            if(m_Sound)
            {
                UI::Text(Format("Channels: {}", m_Sound->GetChannels()));
                UI::Text(Format("Sound Type: {}", SoundTypeToString(m_Sound->GetType())));
                UI::Text(Format("Sound Format: {}", SoundFormatToString(m_Sound->GetFormat())));
                const f32 Seconds = m_Sound->GetDuration();
                const int Minutes = Math::IntegerPart(Seconds / 60.0f);
                const int RemainSeconds = ((int)Seconds) % 60;
                UI::Text(Format("Duration: {:02}:{:02}", Minutes, RemainSeconds));
            }
            
            ImGui::Separator();
            const bool Playing = IsPlaying();
            const char* Label = IsPlaying() ? "Stop" : "Play";
            
            if (UI::Button(Label, {}, m_Sound.get()))
            {
                if(!Playing) Play(); else Stop();
            }

            ImGui::SameLine();
            if (ImGui::Button("Browse"))
            {
                const Path NewFile = File::OpenFileDialog("Choose a new audio file", "", "*wav");
                if (File::Exists(NewFile))
                {
                    Stop();
                    SoundFlags Options = m_Sound ? m_Sound->GetFlags() : SoundFlags(SoundFlagBits::Default);
                    if (const Ref<Sound> NewSound = Sound::CreateFromFile(NewFile, Options))
                    {
                        m_Sound.reset();
                        SetSound(NewSound);
                    }
                }
                else
                {
                    Ref<PopupMessage> Message = PopupMessage::Create(
                        "Error",
                        "Failed to load sound!",
                        PopupMessageResponse::OK,
                        PopupMessageIcon::Error);

                    Message->Show();
                }
            }

            
            ImGui::SameLine();
            if (ImGui::Button("Unload"))
            {
                Stop();
                m_Sound.reset();
            }
            
            ImGui::TreePop();
        }
        
        UI::DragValue<f32>("Volume", m_Volume, 0.01f, 0.0f, 1.0f, "%.2f");
        UI::DragValue<f32>("Pitch", m_Pitch, 0.01f, 0.0f, 10.0f, "%.2f");
        ImGui::Checkbox("Looping", &m_Looping);
    }



    void SoundEmitter::Play()
    {
        if(!m_Sound)
        {
            HYDRO_LOG(SoundEmitter, Verbosity::Error, "Tried to play a SoundEmitter that had no sound!");
            return;
        }

        const AudioSystem& AudioSystem = g_Application->GetAudioSystem();
        FMOD::System* Handle = AudioSystem.GetHandle();
        Handle->playSound(m_Sound->GetHandle(), nullptr, false, &m_Channel);
        OnStartedEvent.Broadcast(m_Sound, false);
    }

    void SoundEmitter::Stop()
    {
        m_Channel->stop();
        OnStopEvent.Broadcast(m_Sound, false);
    }

    void SoundEmitter::Pause()
    {
        m_Channel->setPaused(true);
        OnStopEvent.Broadcast(m_Sound, true);
    }

    void SoundEmitter::Resume()
    {
        m_Channel->setPaused(false);
        OnStartedEvent.Broadcast(m_Sound, true);
    }

    Ref<Sound> SoundEmitter::GetSound() const
    {
        return m_Sound;
    }

    void SoundEmitter::SetSound(const Ref<Sound>& Clip)
    {
        if(IsPlaying()) Stop();
        m_Sound = Clip;
    }

    void SoundEmitter::SetVolume(f32 Vol)
    {
        m_Volume = Vol;
    }

    void SoundEmitter::SetPitch(f32 Pitch)
    {
        m_Pitch = Pitch;
    }

    f32 SoundEmitter::GetVolume() const
    {
        return m_Volume;
    }

    f32 SoundEmitter::GetPitch() const
    {
        return m_Pitch;
    }

    void SoundEmitter::OnPlaying(Ref<Sound> Sound, u32 Position, u32 Length)
    {
        m_PlaybackPosition = Position;
        m_Length = Length;
    }

    bool SoundEmitter::IsPlaying() const
    {
        if(!m_Channel) return false;
        bool Result;
        m_Channel->isPlaying(&Result);
        return Result;
    }
}
