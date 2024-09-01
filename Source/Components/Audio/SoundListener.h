#pragma once
#include "Core/Component.h"

namespace FMOD
{
    class System;
}

namespace Hydro
{
    class SoundListener : public Component
    {
    public:
        SoundListener(Entity* Owner);

        void OnInit() override;
        void OnDestroy() override;
        void OnStart() override;
        void OnUpdate(float Delta) override;
        void OnInspectorGUI(const ImGuiIO& IO) override;
        void SetIndex(uint32 Index);
    private:
        uint32 m_Index = 0;
    };
}
