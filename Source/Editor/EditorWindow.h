#pragma once
#include "Platform/PlatformImGui.h"

namespace Hydro
{
    class EditorWindow
    {
    public:
        EditorWindow(std::string Name);
        virtual ~EditorWindow() = default;
        virtual void OnInit(){}
        virtual void OnUpdate(float Delta){}
        virtual void OnInspectorGUI(const ImGuiIO& IO){}

        bool* OpenedPtr();
        bool IsOpened() const;
    

    protected:
        std::string m_Name;
        bool m_Opened;
        GUID m_guid;
    };
}
