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
        SoundListener(GameObject* Owner);

        void OnInit() override;
        void OnDestroy() override;
        void OnStart() override;
        void OnUpdate(float Delta) override;
        void OnInspectorGUI(const ImGuiIO& IO) override;
        void SetIndex(uint32_t Index);
    private:
        FMOD::System* m_System = nullptr;
        uint32_t m_Index = 0;
    };
}
