#pragma once
#include "Platform/PlatformImGui.h"
#include "Core/GUID.h"
#include "Core/Containers/String.h"

namespace Hydro
{
    class EditorWindow
    {
    public:
        EditorWindow(String Name);
        virtual ~EditorWindow() = default;
        virtual void OnInit(){}
        virtual void OnUpdate(f32 Delta){}
        virtual void OnInspectorGUI(const ImGuiIO& IO){}

        bool* OpenedPtr();
        bool IsOpened() const;
    

    protected:
        String m_Name;
        bool m_Opened;
        GUID m_Guid;
    };
}
