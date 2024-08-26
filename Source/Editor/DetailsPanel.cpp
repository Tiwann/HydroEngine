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

            UI::Text(Format("GUID: {}", SelectedObject->GetGuid().GetString()));
            static bool ShowContextMenu;
            SelectedObject->ForEach([&IO](const auto& Component)
            {
                ImGui::PushID(Component->GetGuid());
                if (ImGui::TreeNode(Component->GetName().c_str()))
                {
                    Component->OnInspectorGUI(IO);
                    ImGui::TreePop();
                }
                ImGui::PopID();

                if(UI::ItemClicked(MouseButton::Right))
                {
                    ShowContextMenu = true;
                    ImGui::OpenPopup("ComponentContextMenu");
                    Selection::SetComponent(Component);
                }
                
            });


            if (ShowContextMenu && ImGui::BeginPopup("ComponentContextMenu"))
            {
                const char* Options[]
                {
                    "Delete"
                };

                ImGui::SeparatorText("Context Menu");
                for (size_t i = 0; i < std::size(Options); i++)
                {
                    if (ImGui::Selectable(Options[i]))
                    {
                        Ref<Component> SelectedComponent = Selection::GetComponent();
                        if(!SelectedObject) break;
                            
                        switch (i)
                        {
                        case 0: SelectedObject->RemoveComponent(SelectedComponent);
                        }
                        ShowContextMenu = false;
                    }
                }

                ImGui::EndPopup();
            }
        });
    }
}
