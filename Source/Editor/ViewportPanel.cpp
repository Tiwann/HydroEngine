#include "HydroPCH.h"
#include "ViewportPanel.h"
#include "EditorGUI.h"
#include "StyleVar.h"
#include "Core/Application.h"
#include "Core/FrameBuffer.h"
#include "Core/Texture2D.h"

namespace
{
    inline const Hydro::Vector2 WindowStartSize(960, 540);
}

namespace Hydro
{
    void ViewportPanel::OnInit()
    {
        EditorWindow::OnInit();

        m_FrameBuffer = FrameBuffer::Create(FrameBufferAttachment::Color);
        m_FrameBuffer->Resize(WindowStartSize);
        if(!m_FrameBuffer->Validate())
        {
            HYDRO_LOG(ViewportWindow, Verbosity::Error, "Failed to validate framebuffer!");
        }
    }

    void ViewportPanel::OnUpdate(float Delta)
    {
        EditorWindow::OnUpdate(Delta);
        m_FrameBuffer->Resize(m_Size);
    }

    void ViewportPanel::OnInspectorGUI(const ImGuiIO& IO)
    {
        EditorWindow::OnInspectorGUI(IO);


        UI::ScopedStyleVarPusher WindowPadding(UI::StyleVar::WindowPadding, Vector2::Zero);
        ImGui::SetNextWindowSize(WindowStartSize, ImGuiCond_Appearing);
        UI::NewWindow(m_Name, m_Opened, WindowFlagBits::None, [this]
        {
            m_Size = ImGui::GetContentRegionAvail();
            m_Position = ImGui::GetWindowPos();
            ImGui::Image(m_FrameBuffer->GetAttachedTexture()->As<ImTextureID>(), m_Size, {0, 1}, {1, 0});
            m_DrawList = ImGui::GetWindowDrawList();
            if(!m_Available) m_Available = true;
        });
    }

    bool ViewportPanel::IsAvailable() const
    {
        return m_Available;
    }


    Vector2 ViewportPanel::GetSize() const
    {
        return m_Size;
    }

    Ref<FrameBuffer> ViewportPanel::GetFrameBuffer() const
    {
        return m_FrameBuffer;
    }

    ImDrawList* ViewportPanel::GetDrawList() const
    {
        return m_DrawList;
    }
}
