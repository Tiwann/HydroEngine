#pragma once
#include "EditorWindow.h"
#include "Core/LogCategory.h"

HYDRO_DECLARE_LOG_CATEGORY_STATIC(DetailsPanel, "DETAILS PANEL")

namespace Hydro
{
    class DetailsPanel : public EditorWindow
    {
    public:
        DetailsPanel(class Scene* InScene);
        void OnInspectorGUI(const ImGuiIO& IO) override;

    private:
        Scene* m_CurrentScene;
    };
}
