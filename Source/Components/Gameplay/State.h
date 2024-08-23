#pragma once

namespace Hydro
{
    template<typename StateMachine>
    class State
    {
    public:
        State(StateMachine* InStateMachine) : m_StateMachine(InStateMachine){}
        virtual ~State() = default;
        virtual void OnEnter(){}
        virtual void OnUpdate(float Delta){}
        virtual void OnPhysicsUpdate(float Delta){}
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
