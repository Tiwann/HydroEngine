#include "HydroPCH.h"
#include "ViewportWindow.h"
#include "EditorGUI.h"

namespace Hydro
{
    void ViewportWindow::OnInit()
    {
        EditorWindow::OnInit();
    }

    void ViewportWindow::OnUpdate(float Delta)
    {
        EditorWindow::OnUpdate(Delta);
    }

    void ViewportWindow::OnInspectorGUI(const ImGuiIO& IO)
    {
        EditorWindow::OnInspectorGUI(IO);
        if(!m_Opened) return;
        
        UI::NewWindow(m_Name, m_Opened, WindowFlagBits::None, [this]
        {
            const ImVec2 WindowSize = ImGui::GetWindowSize();
            m_Size = { WindowSize.x, WindowSize.y };
        });
    }
    

    Vector2 ViewportWindow::GetSize() const
    {
        return m_Size;
    }
}
