#include "HydroPCH.h"
#include "Timer.h"

namespace Hydro
{
    Timer::Timer(float Duration, bool Loop, const std::function<void()>& Callback)
        : m_Started(false), m_Loop(Loop), m_Duration(Duration)
    {
        OnTimerFinish += Callback;
    }

    void Timer::Start()
    {
        m_Started = true;
    }

    void Timer::Stop()
    {
        m_Started = false;
    }

    void Timer::Update(float Delta)
    {
        if(!m_Started) return;
        
        m_Time += Delta;
        if(m_Time >= m_Duration)
        {
            m_Time = 0.0f;
            if(OnTimerFinish.IsBound()) OnTimerFinish.Broadcast();
            if(!m_Loop) m_Started = false;
        }
    }
}
