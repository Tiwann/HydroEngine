#pragma once
#include "MulticastDelegate.h"
#include <GLFW/glfw3.h>

namespace Hydro
{
    class ScopedTimer
    {
    public:
        using FinishedDelegate = MulticastDelegate<void(f32 Duration)>;
        FinishedDelegate FinishedEvent;
        
        ScopedTimer(const FinishedDelegate::DelegateType& OnFinished)
        {
            FinishedEvent.Bind(OnFinished);
            m_Start = glfwGetTime();
        }
        
        ~ScopedTimer()
        {
            m_End = glfwGetTime();
            const f32 Duration = (f32)(m_End - m_Start);
            FinishedEvent.BroadcastChecked(Duration);
            FinishedEvent.ClearAll();
        }
    private:
        f64 m_Start;
        f64 m_End;
    };
}
