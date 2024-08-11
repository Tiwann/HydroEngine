#pragma once
#include "MulticastDelegate.h"

namespace Hydro
{
    template<typename T = std::chrono::seconds>
    class ScopedTimer
    {
    public:
        using ScopedTimerFinishedDelegate = MulticastDelegate<void(float Duration)>;
        ScopedTimerFinishedDelegate FinishedEvent;
        
        ScopedTimer(const ScopedTimerFinishedDelegate::DelegateType& OnFinished)
        {
            FinishedEvent.Bind(OnFinished);
            m_Start = std::chrono::high_resolution_clock::now();
        }
        
        ~ScopedTimer()
        {
            m_End = std::chrono::high_resolution_clock::now();
            const auto Duration = duration_cast<T>(m_End - m_Start).count();
            FinishedEvent.BroadcastChecked((float)Duration / T::period::den);
            FinishedEvent.ClearAll();
        }
    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> m_Start;
        std::chrono::time_point<std::chrono::high_resolution_clock> m_End;
    };
}
