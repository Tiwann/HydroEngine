#pragma once
#include "Core/NumericTypes.h"

namespace Hydro
{
    template<typename StateMachine>
    class State
    {
    public:
        State(StateMachine* InStateMachine) : m_StateMachine(InStateMachine){}
        virtual ~State() = default;
        virtual void OnEnter(){}
        virtual void OnUpdate(f32 Delta){}
        virtual void OnPhysicsUpdate(f32 Delta){}
        virtual void OnExit(){}
        
        void SetStateMachine(StateMachine* InStateMachine)
        {
            m_StateMachine = InStateMachine;
        }
        
        StateMachine* GetStateMachine() const
        {
            return m_StateMachine;
        }

    protected:
        StateMachine* m_StateMachine = nullptr;
    };
}
