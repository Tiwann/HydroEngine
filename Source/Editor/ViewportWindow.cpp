#include "HydroPCH.h"
#include "ViewportWindow.h"
#include "EditorGUI.h"
#include "StyleVar.h"
#include "Core/FrameBuffer.h"
#include "Core/Texture2D.h"

namespace Hydro
{
    void ViewportPanel::OnInit()
    {
        EditorWindow::OnInit();

        m_FrameBuffer = FrameBuffer::Create(FrameBufferAttachment::Color);
        Ref<Texture2D> Texture = m_FrameBuffer->GetAttachedTexture();
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
        if(!m_Opened) return;

        
        ImGui::PushID(m_guid);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        if(ImGui::Begin(m_Name.data(), &m_Opened, WindowFlags(WindowFlagBits::NoScrollbar).As<ImGuiWindowFlags>()))
        {
            m_Size = ImGui::GetContentRegionAvail();
            ImGui::Image(m_FrameBuffer->GetAttachedTexture()->As<ImTextureID>(), m_Size, {0, 1}, {1, 0});
            m_DrawList = ImGui::GetWindowDrawList();
        }
        ImGui::End();
        ImGui::PopStyleVar();
        ImGui::PopID();
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
