#pragma once
#include "EditorWindow.h"
#include "Core/LogCategory.h"

HYDRO_DECLARE_LOG_CATEGORY_STATIC(SceneHierarchyPanel, "SCENE HIERARCHY PANEL")

namespace Hydro
{
    class SceneHierarchyPanel : public EditorWindow
    {
    public:
        SceneHierarchyPanel(class Scene* InScene);
        void OnInspectorGUI(const ImGuiIO& IO) override;
    
    private:
        Scene* m_CurrentScene;
    };
}


