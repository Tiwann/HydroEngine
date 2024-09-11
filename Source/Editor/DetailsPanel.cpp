#include "DetailsPanel.h"
#include "EditorGUI.h"
#include "Selection.h"
#include "Core/Scene.h"
#include "Core/Containers/StringFormat.h"

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
            Ref<Entity> SelectedEntity = Selection::GetEntity();
            if (!SelectedEntity) return;

            char Buffer[256] = {};
            std::copy(SelectedEntity->GetName().begin(), SelectedEntity->GetName().end(), Buffer);

            ImGui::PushID(SelectedEntity->GetGuid());
            ImGui::PushItemWidth(200);
            if (ImGui::InputText("##", Buffer, 256, ImGuiInputTextFlags_EnterReturnsTrue))
            {
                SelectedEntity->SetName({Buffer});
            }
            ImGui::PopItemWidth();
            
            ImGui::SameLine();
            UI::AddComponent(SelectedEntity);
            ImGui::PopID();

            UI::Text(Format("GUID: {}", SelectedEntity->GetGuid().GetString()));
            static bool ShowContextMenu;
            SelectedEntity->ForEach([&IO](const auto& Component)
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
                        if(!SelectedEntity) break;
                            
                        switch (i)
                        {
                        case 0: SelectedEntity->RemoveComponent(SelectedComponent);
                        }
                        ShowContextMenu = false;
                    }
                }

                ImGui::EndPopup();
            }
        });
    }
}
