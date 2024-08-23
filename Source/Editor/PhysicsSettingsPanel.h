#pragma once
#include "EditorWindow.h"

namespace Hydro
{
    class PhysicsSettingsPanel : public EditorWindow
    {
    public:
        explicit PhysicsSettingsPanel() : EditorWindow("Physics Settings") { }
        void OnInspectorGUI(const ImGuiIO& IO) override;
    };
}
