#include "HydroPCH.h"
#include "ApplicationConfigurationSerializer.h"
#include "Core/Assertion.h"
#include "..\Core\IniParser.h"
#include <fstream>

namespace Hydro
{
    ApplicationConfigurationSerializer::ApplicationConfigurationSerializer(const Path& Filepath) : Serializer(Filepath)
    {
            
    }

    bool ApplicationConfigurationSerializer::Serialize(const ApplicationConfiguration& Configuration)
    {
        WriteWindow(Configuration);
        WriteGraphics(Configuration);
        return true;
    }

    bool ApplicationConfigurationSerializer::Deserialize(ApplicationConfiguration& OutConfiguration)
    {
        return true;
    }

    void ApplicationConfigurationSerializer::WriteWindow(const ApplicationConfiguration& Configuration)
    {
       IniParser Parser(m_Stream);
       Parser.Write("Window", {
           { "Width", std::to_string(Configuration.WindowWidth) },
           { "Height", std::to_string(Configuration.WindowHeight) },
           { "Fullscreen", std::to_string(Configuration.StartFullscreen) },
           { "Resizable", std::to_string(Configuration.WindowResizable) },
           { "ShowRHI", std::to_string(Configuration.ShowGraphicsAPIName) },
           { "ShowConfig", std::to_string(Configuration.ShowConfiguration) },
           { "ShowOS", std::to_string(Configuration.ShowOSName) },
           { "ShowDeltaTime", std::to_string(Configuration.ShowDeltaTime) },
           { "ShowFPS", std::to_string(Configuration.ShowFPS) },
           { "SwapchainBufferType", std::to_string(Configuration.GraphicsSettings.BufferType) },
       }); 
    }

    void ApplicationConfigurationSerializer::WriteGraphics(const ApplicationConfiguration& Configuration) const
    {
        
    }
}
