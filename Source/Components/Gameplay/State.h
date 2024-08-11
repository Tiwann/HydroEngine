#pragma once

namespace Hydro
{
    class State
    {
    protected:
        virtual void OnEnter() = 0;
        virtual void OnUpdate() = 0;
        virtual void OnExit() = 0;
    };
}
