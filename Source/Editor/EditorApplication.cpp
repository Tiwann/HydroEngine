#include "HydroPCH.h"
#include "EditorApplication.h"

namespace Hydro
{
    void EditorApplication::OnInit()
    {
        Application::OnInit();
    }

    void EditorApplication::OnUpdate(float Delta)
    {
        Application::OnUpdate(Delta);
    }

    void EditorApplication::OnGui()
    {
        Application::OnGui();
    }

    ApplicationConfiguration EditorApplication::CreateConfiguration() const
    {
        ApplicationConfiguration Configuration;
        Configuration.AppName = "Hydro Editor";
        Configuration.WithEditor = true;
        Configuration.Graphics = GraphicsSettings::DefaultSettings;
        Configuration.WindowWidth = 1920;
        Configuration.WindowHeight = 1080;
        Configuration.StartFullscreen = false;
        Configuration.ShowGraphicsAPIName = true;
        Configuration.WindowResizable = true;
        return Configuration;
    }
}
