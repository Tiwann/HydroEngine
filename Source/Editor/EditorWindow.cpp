#include "HydroPCH.h"
#include "EditorWindow.h"


namespace Hydro
{
    EditorWindow::EditorWindow(std::string Name): m_Name(std::move(Name)), m_Opened(false)
    {
        
    }

    bool* EditorWindow::OpenedPtr()
    {
        return &m_Opened;
    }

    bool EditorWindow::IsOpened() const
    {
        return m_Opened;
    }
}