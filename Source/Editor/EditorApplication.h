#pragma once
#include "Core/Application.h"

namespace Hydro
{
    class EditorApplication : public Application
    {
    public:
        void OnInit() override;
        void OnUpdate(float Delta) override;
        void OnGui() override;
        ApplicationConfiguration CreateConfiguration() const override;
    private:
    };
}
