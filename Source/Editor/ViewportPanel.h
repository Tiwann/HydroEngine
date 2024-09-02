#pragma once
#include "EditorWindow.h"
#include "Core/LogCategory.h"
#include "Math/Vector2.h"
#include "Core/SharedPointer.h"

HYDRO_DECLARE_LOG_CATEGORY_STATIC(ViewportWindow, "VIEWPORT")

namespace Hydro
{
    class FrameBuffer;
}

namespace Hydro
{
    class ViewportPanel : public EditorWindow
    {
    public:
        ViewportPanel() : EditorWindow("Viewport")
        {
            m_Opened = true;
        }

        void OnInit() override;
        void OnUpdate(f32 Delta) override;
        void OnInspectorGUI(const ImGuiIO& IO) override;

        bool IsAvailable() const;

        Vector2 GetSize() const;
        Vector2 GetPosition() const { return m_Position; }
        Ref<FrameBuffer> GetFrameBuffer() const;
        ImDrawList* GetDrawList() const;

    private:
        Ref<FrameBuffer> m_FrameBuffer;
        Vector2 m_Size;
        Vector2 m_Position;
        ImDrawList* m_DrawList = nullptr;
        bool m_Available = false;
    };
}
