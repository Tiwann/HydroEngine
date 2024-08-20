#pragma once
#include "MulticastDelegate.h"
#include <GLFW/glfw3.h>

namespace Hydro
{
    class ScopedTimer
    {
    public:
        using FinishedDelegate = MulticastDelegate<void(float Duration)>;
        FinishedDelegate FinishedEvent;
        
        ScopedTimer(const FinishedDelegate::DelegateType& OnFinished)
        {
            FinishedEvent.Bind(OnFinished);
            m_Start = glfwGetTime();
        }
        
        ~ScopedTimer()
        {
            m_End = glfwGetTime();
            const float Duration = (float)(m_End - m_Start);
            FinishedEvent.BroadcastChecked(Duration);
            FinishedEvent.ClearAll();
        }
    private:
        double m_Start;
        double m_End;
    };
}
