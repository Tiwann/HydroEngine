#pragma once

namespace Hydro
{
    class State
    {
    public:
        virtual ~State() = default;
        virtual void OnEnter() = 0;
        virtual void OnUpdate(float Delta) = 0;
        virtual void OnExit() = 0;
    };
}
