#include "HydroPCH.h"
#include "Serialization/ApplicationConfigurationSerializer.h"

#include <fstream>

#include "Core/StringFormat.h"

namespace Hydro
{
    ApplicationConfigurationSerializer::ApplicationConfigurationSerializer(const String& filepath) : Serializer(*filepath)
    {
            
    }

    bool ApplicationConfigurationSerializer::Serialize(const ApplicationConfiguration& Configuration)
    {
        m_File = fopen(*m_Filepath, "w");
        if(!m_File)
        {
            HYDRO_LOG_ERROR("[SERIALIZER] Failed to open file");
        }
        
        WriteWindow(Configuration);
        WriteGraphics(Configuration);
        return true;
    }

    bool ApplicationConfigurationSerializer::Deserialize(ApplicationConfiguration& OutConfiguration)
    {
        m_File = fopen(*m_Filepath, "r");
        if(!m_File)
        {
            HYDRO_LOG_ERROR("[SERIALIZER] Failed to open file");
        }

        std::fstream stream(m_File);

        while(stream.good())
        {
            std::string line;
            std::getline(stream, line);
            
            if(line == "[Window]")
            {
                ReadWindow(OutConfiguration);
            } else if(line == "[Graphics]")
            {
                ReadGraphics(OutConfiguration);
            }
        }
        return true;
    }

    void ApplicationConfigurationSerializer::WriteWindow(const ApplicationConfiguration& Configuration) const
    {
        const String format = 
            "[Window]\n"
            "Width = %d\n"
            "Height = %d\n"
            "Resizable = %d\n"
            "ShowGraphicsAPIName = %d\n"
            "ShowOSName = %d\n"
            "ShowConfiguration = %d\n"
            "ShowDeltaTime = %d\n"
            "ShowFPS = %d\n"
            "WindowTitleUpdateTime = %.1f\n\n";

        const String Data = Format(format,
                                   Configuration.WindowWidth,
                                   Configuration.WindowHeight,
                                   Configuration.WindowResizable,
                                   (int)Configuration.ShowGraphicsAPIName,
                                   (int)Configuration.ShowOSName,
                                   (int)Configuration.ShowConfiguration,
                                   (int)Configuration.ShowDeltaTime,
                                   (int)Configuration.ShowFPS,
                                   Configuration.WindowTitleUpdateTime);
        
        fwrite(*Data, 1, Data.Size(), m_File);
    }

    void ApplicationConfigurationSerializer::WriteGraphics(const ApplicationConfiguration& Configuration) const
    {
        const String format = "[Graphics]\n"
        "SwapchainBufferNum = %d";

        const String Data = Format(format, (int)Configuration.GraphicsSettings.BufferType);
        fwrite(*Data, 1, Data.Size(), m_File);
    }

    bool ApplicationConfigurationSerializer::ReadWindow(ApplicationConfiguration& OutConfiguration)
    {
        return false;
    }

    bool ApplicationConfigurationSerializer::ReadGraphics(ApplicationConfiguration& OutConfiguration)
    {
        return false;
    }
}
