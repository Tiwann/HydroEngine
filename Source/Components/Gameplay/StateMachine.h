#pragma once
#include "State.h"
#include "Core/Component.h"

namespace Hydro
{
    template<typename StateBase, typename = std::enable_if_t<std::is_base_of_v<State, StateBase>>>
    class StateMachine : public Component
    {
    public:
        StateMachine(GameObject* Owner) : Component(Owner, "StateMachine"){}
        
        void ChangeState(const StateBase& NewState)
        {
            m_CurrentState->OnExit();
            m_CurrentState = &NewState;
            m_CurrentState->OnExit();
        }
        
        const StateBase& GetCurrentState() const
        {
            return *m_CurrentState;
        }

        void SetCurrentState(const StateBase& NewState)
        {
            m_CurrentState = &NewState;
        }

        void OnUpdate(float Delta) override
        {
            
        }

    private:
        StateBase* m_CurrentState = nullptr;
    };
}
