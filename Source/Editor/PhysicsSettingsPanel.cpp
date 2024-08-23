#include "PhysicsSettingsPanel.h"
#include "EditorGUI.h"
#include "Core/Physics/Physics2D.h"
#include "Core/Physics/Physics3D.h"

namespace Hydro
{
    void PhysicsSettingsPanel::OnInspectorGUI(const ImGuiIO& IO)
    {
        EditorWindow::OnInspectorGUI(IO);
        if(!m_Opened) return;

        UI::NewWindow(m_Name, m_Opened, WindowFlagBits::None, []
        {
            ImGui::SeparatorText("Physics2D");
            UI::DragVector2<float>("Base Gravity", Physics2D::Gravity, 0.01f);
            UI::DragValue<float>("Timestep", Physics2D::TimeStep, 0.01f);

            ImGui::SeparatorText("Physics3D");
            UI::DragVector3<float>("Base Gravity", Physics3D::Gravity, 0.01f);
            UI::DragValue<float>("Timestep", Physics3D::TimeStep, 0.01f);
        });
        
    }
}
