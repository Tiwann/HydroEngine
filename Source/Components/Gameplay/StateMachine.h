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
    template<typename StateBase>
    class StateMachine : public Component
    {
    protected:
        StateMachine(Entity* Owner, const std::string& Name = "StateMachine") : Component(Owner, Name) {}
    public:
        void ChangeState(StateBase* NewState)
        {
            m_CurrentState->OnExit();
            m_CurrentState = NewState;
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

        void OnStart() override
        {
            m_CurrentState->OnEnter();
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

        void OnDestroy() override
        {
            m_CurrentState->OnExit();
        }

    protected:
        StateBase* m_CurrentState = nullptr;
    };
}
