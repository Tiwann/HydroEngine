#pragma once
#include "State.h"
#include "Core/Component.h"
#include "Core/LogCategory.h"
#include "Core/Log.h"
#include "Core/LogVerbosity.h"
#include "Core/TypeTraits.h"

HYDRO_DECLARE_LOG_CATEGORY_STATIC(StateMachine, "STATE MACHINE")

namespace Hydro
{
    template<typename StateBase, typename = EnableIfType<IsBaseOfValue<State, StateBase>>>
    class StateMachine : public Component
    {
    protected:
        StateMachine(GameObject* Owner, const std::string& Name = "StateMachine") : Component(Owner, Name) {}
    public:
        void ChangeState(const StateBase& NewState)
        {
            m_CurrentState->OnExit();
            m_CurrentState = &NewState;
            m_CurrentState->OnEnter();
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
            if(!m_CurrentState)
            {
                HYDRO_LOG(StateMachine, Verbosity::Error, "Current state is null, cannot update state machine");
                return;
            }

            m_CurrentState->OnUpdate(Delta);
        }

    private:
        StateBase* m_CurrentState = nullptr;
    };
}
