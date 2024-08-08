#pragma once
#include "MulticastDelegate.h"

namespace Hydro
{
    class Timer
    {
    public:
        explicit Timer(float Duration, bool Loop, const std::function<void()>& CallbackSubcribers);

        void Start();
        void Stop();
        void Update(float Delta);
        
        MulticastDelegate<void()> OnTimerFinish;
    private:
        float m_Time{0.0f};
        bool m_Started;
        bool m_Loop;
        float m_Duration;
        
    };
}
