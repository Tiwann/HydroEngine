#include "HydroPCH.h"
#include "DetailsPanel.h"

#include "EditorGUI.h"
#include "Selection.h"
#include "Core/Scene.h"

namespace Hydro
{
    DetailsPanel::DetailsPanel(Scene* InScene) : EditorWindow("Details"), m_CurrentScene(InScene)
    {
        m_Opened = true;
    }
    
    void DetailsPanel::OnInspectorGUI(const ImGuiIO& IO)
    {
        EditorWindow::OnInspectorGUI(IO);
        UI::NewWindow(m_Name, m_Opened, WindowFlagBits::None, [&IO]
        {
            Ref<GameObject> SelectedObject = Selection::GetGameObject();
            if (!SelectedObject) return;

            char Buffer[256] = {};
            std::ranges::copy(SelectedObject->GetName(), Buffer);

            ImGui::PushID(SelectedObject->GetGuid());
            ImGui::PushItemWidth(200);
            if (ImGui::InputText("##", Buffer, 256, ImGuiInputTextFlags_EnterReturnsTrue))
            {
                SelectedObject->SetName({Buffer});
            }
            ImGui::PopItemWidth();
            
            ImGui::SameLine();
            UI::AddComponent(SelectedObject);
            ImGui::PopID();

            UI::Text(fmt::format("GUID: {}", SelectedObject->GetGuid().GetString()));
            SelectedObject->ForEach([&IO](const auto& Component)
            {
                ImGui::PushID(Component->GetGuid());
                if (ImGui::TreeNode(Component->GetName().c_str()))
                {
                    Component->OnInspectorGUI(IO);
                    ImGui::TreePop();
                }
                ImGui::PopID();
            });
        });
    }
}
