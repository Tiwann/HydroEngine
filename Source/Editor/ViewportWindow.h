#pragma once
#include "EditorWindow.h"
#include "Math/Vector2.h"

namespace Hydro
{
    class ViewportWindow : public EditorWindow
    {
    public:
        ViewportWindow() : EditorWindow("Viewport")
        {
            m_Opened = true;
        }

        void OnInit() override;
        void OnUpdate(float Delta) override;
        void OnInspectorGUI(const ImGuiIO& IO) override;
        
        Vector2 GetSize() const;
    private:
        Vector2 m_Size;
    };
}
