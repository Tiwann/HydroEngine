#pragma once
#include "MulticastDelegate.h"

namespace Hydro
{
    class Timer
    {
    public:
        using FinishedDelegate = MulticastDelegate<void()>;
        Timer() = default;
        Timer(float Duration, bool Loop, const FinishedDelegate::DelegateType& Callback);
        ~Timer();

        void Reset();
        void Start();
        void Stop();
        void Update(float Delta);

        void SetLoop(bool Loop);
        void SetDuration(float Duration);

        FinishedDelegate FinishedEvent;
    private:
        float m_Time{0.0f};
        bool m_Started{false};
        bool m_Loop{false};
        float m_Duration{0.0f};
    };
}
