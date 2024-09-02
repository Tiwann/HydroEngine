#include "SceneHierarchyPanel.h"
#include "EditorGUI.h"
#include "Selection.h"
#include "ViewportPanel.h"
#include "Components/Transform.h"
#include "Components/Camera.h"
#include "Components/Physics/RigidBody2D.h"
#include "Core/Application.h"
#include "Core/RendererBackend.h"
#include "Core/Scene.h"
#include "ImGuizmo/ImGuizmo.h"


namespace Hydro
{
    SceneHierarchyPanel::SceneHierarchyPanel(Scene* InScene) : EditorWindow("Scene Hierarchy"), m_CurrentScene(InScene)
    {
        m_Opened = true;
    }

    static void DrawEntity(const Ref<Entity>& Entity)
    {
        const char* Name = Entity->GetName().empty() ? "##" : Entity->GetName().c_str();
        
        if(ImGui::TreeNode(Name))
        {
            if(Entity->HasChildren())
            {
                const auto& Child = Entity->GetChild(0);
                DrawEntity(Child);
            }
            ImGui::TreePop();
        }
    }
    
    void SceneHierarchyPanel::OnInspectorGUI(const ImGuiIO& IO)
    {
        EditorWindow::OnInspectorGUI(IO);
        if(!m_Opened) return;

        if(ImGui::Begin(*m_Name, &m_Opened))
        {
            if(ImGui::Button("Create Entity"))
            {
                m_CurrentScene->CreateEntity("Empty Entity");    
            }

            static bool ShowContextMenu = false;
            
            m_CurrentScene->ForEach([this](const Ref<Entity>& Entity)
            {
                DrawEntity(Entity);
                if(UI::ItemClicked(MouseButton::Left))
                {
                    HYDRO_LOG(SceneHierarchyPanel, Verbosity::Warning, "Item Cliked: {}", Entity->GetName().c_str());
                    Selection::SetEntity(Entity);
                }

                
                if(UI::ItemClicked(MouseButton::Right))
                {
                    ShowContextMenu = true;
                    ImGui::OpenPopup("ContextMenu");
                    Selection::SetEntity(Entity);
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
                        Ref<Entity> SelectedEntity = Selection::GetEntity();
                        if(!SelectedEntity) break;
                            
                        switch (i)
                        {
                        case 0: m_CurrentScene->DestroyEntity(SelectedEntity); break;
                        }
                        ShowContextMenu = false;
                    }
                }

                ImGui::EndPopup();
            }

            if(Ref<Entity> Entity = Selection::GetEntity())
            {
                const Application& App = *g_Application;
                const Vector2 ViewportSize = App.GetViewportPanel()->GetSize();
                const Vector2 ViewportPos = App.GetViewportPanel()->GetPosition();
                const Ref<Camera> Cam = App.GetRendererBackend()->GetCurrentCamera();
                if(!Cam) return;

                ImGuizmo::SetOrthographic(Cam->Settings.Projection == CameraProjectionType::Orthographic);
                ImGuizmo::SetDrawlist(App.GetViewportPanel()->GetDrawList());
                ImGuizmo::SetRect(ViewportPos.x, ViewportPos.y, ViewportSize.x, ViewportSize.y);

                const Ref<Transform> Transform = Entity->GetTransform();
                Matrix4 ModelMatrix = Transform->GetLocalSpaceMatrix();
                Matrix4 ViewMatrix = Cam->GetViewMatrix();
                Matrix4 ProjectionMatrix = Cam->GetProjectionMatrix();
                
                ImGuizmo::Manipulate(*ViewMatrix, *ProjectionMatrix, ImGuizmo::UNIVERSAL, ImGuizmo::LOCAL, *ModelMatrix);
                if(ImGuizmo::IsUsing())
                {
                    Vector3 Pos, Rot, Sc;
                    ImGuizmo::DecomposeMatrixToComponents(*ModelMatrix, Pos, Rot, Sc);
                    Transform->SetPosition(Pos);
                    Transform->SetRotation(Rot);
                    Transform->SetScale(Sc);

                    if(const auto& Shape = Entity->GetComponent<RigidBody2D>())
                    {
                        Shape->SetPosition(Pos);
                        Shape->SetRotation(Rot.z);
                        Shape->RecreatePhysicsState();
                    }
                }
            }
        }
        ImGui::End();
        

       
    }
}
