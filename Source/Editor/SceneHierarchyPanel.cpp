#include "HydroPCH.h"
#include "SceneHierarchyPanel.h"

#include "EditorGUI.h"
#include "Selection.h"
#include "Components/Camera.h"
#include "Core/Application.h"
#include "Core/RendererBackend.h"
#include "Core/Scene.h"
#include "Core/Window.h"
#include "ImGuizmo/ImGuizmo.h"


namespace Hydro
{
    SceneHierarchyPanel::SceneHierarchyPanel(Scene* InScene) : EditorWindow("Scene Hierarchy"), m_CurrentScene(InScene)
    {
        m_Opened = true;
    }

    static void DrawGameObject(const Ref<GameObject>& Object)
    {
        const char* Name = Object->GetName().empty() ? "##" : Object->GetName().c_str();
        
        if(ImGui::TreeNode(Name))
        {
            if(Object->HasChildren())
            {
                const auto& Child = Object->GetChild(0);
                DrawGameObject(Child);
            }
            ImGui::TreePop();
        }
    }
    
    void SceneHierarchyPanel::OnInspectorGUI(const ImGuiIO& IO)
    {
        EditorWindow::OnInspectorGUI(IO);
        if(!m_Opened) return;
        
        UI::NewWindow(m_Name, m_Opened, WindowFlagBits::None, [this]
        {
            if(ImGui::Button("Create Object"))
            {
                m_CurrentScene->CreateObject("New Object");    
            }

            static bool ShowContextMenu = false;
            
            m_CurrentScene->ForEach([this](const Ref<GameObject>& Object)
            {
                DrawGameObject(Object);
                if(UI::ItemClicked(MouseButton::Left))
                {
                    HYDRO_LOG(SceneHierarchyPanel, Verbosity::Warning, "Item Cliked: {}", Object->GetName().c_str());
                    Selection::Set(Object.get());
                    Selection::SetGameObject(Object);
                }

                
                if(UI::ItemClicked(MouseButton::Right))
                {
                    ShowContextMenu = true;
                    ImGui::OpenPopup("ContextMenu");
                    Selection::SetGameObject(Object);
                }
                
            });

            if (ShowContextMenu && ImGui::BeginPopup("ContextMenu"))
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
                        Ref<GameObject> SelectedObject = Selection::GetGameObject();
                        if(!SelectedObject) break;
                            
                        switch (i)
                        {
                        case 0: m_CurrentScene->DestroyObject(SelectedObject); break;
                        }
                        ShowContextMenu = false;
                    }
                }

                ImGui::EndPopup();
            }
        });

        if(Ref<GameObject> Object = Selection::GetGameObject())
        {
            Application& App = Application::GetCurrentApplication();
            Vector2 Size = App.GetWindow()->GetSize();
            Ref<Camera> Cam = App.GetRendererBackend()->GetCurrentCamera();

            ImGuizmo::SetOrthographic(Cam->Settings.Projection == CameraProjectionType::Orthographic);
            ImGuizmo::SetDrawlist(ImGui::GetBackgroundDrawList());
            ImGuizmo::SetRect(0, 0, Size.x, Size.y);

            Ref<Transform> Tr = Object->GetTransform();
            Matrix4 Mat = Tr->GetLocalSpaceMatrix();
            
            ImGuizmo::Manipulate(Cam->GetViewMatrix().ValuePtr(), Cam->GetProjectionMatrix().ValuePtr(),
                ImGuizmo::TRANSLATE, ImGuizmo::LOCAL, Mat.ValuePtr());
            if(ImGuizmo::IsUsing())
            {
                Vector3 Pos, Rot, Sc;
                ImGuizmo::DecomposeMatrixToComponents(Mat.ValuePtr(), Pos.ValuePtr(), Rot.ValuePtr(), Sc.ValuePtr());
                Tr->SetPosition(Pos);
                Tr->SetRotation(Rot);
                Tr->SetScale(Sc);
            }
        }
    }
}
