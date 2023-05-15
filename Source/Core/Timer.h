#pragma once
#include "HydroPCH.h"
#include "Function.h"

namespace Hydro
{
    class HYDRO_API Timer
    {
    public:
        Timer(float Duration, bool Loop, bool Start, Function<void> Callback) :
        m_Duration(Duration), m_Loop(Loop), m_Callback(Callback)
        {
            if(Start) this->Start();
        }

        void Start()
        {
            m_Running = true;
        }

        void Stop()
        {
            m_Running = false;
        }

        void OnUpdate(float Delta)
        {
            if (m_Running)
            {
                m_Timer += Delta;
                if (m_Timer >= m_Duration)
                {
                    m_Callback.CallChecked();
                    if (m_Loop)
                        m_Timer = 0.0f;
                    else
                    {
                        m_Timer = 0.0f;
                        m_Running = false;
                    }
                }
            }
        }

        void SetDuration(float Duration)
        {
            m_Duration = Duration;
        }

        void SetLooping(bool Loop)
        {
            m_Loop = Loop;
        }

        void RegisterCallback(Function<void> Callback)
        {
            m_Callback = Callback;
        }
        
    private:
        float m_Duration = 0.0f;
        bool m_Loop = false;
        float m_Timer = 0.0f;
        bool m_Running = false;
        Function<void> m_Callback;
    };
}