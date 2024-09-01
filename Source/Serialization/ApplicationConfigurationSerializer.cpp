#include "ApplicationConfigurationSerializer.h"
#include <fstream>
#include <nlohmann/json.hpp>

namespace Hydro
{
    
    bool ApplicationConfigurationSerializer::Serialize(const ApplicationConfiguration& Configuration, const Path& Filepath)
    {
        std::ofstream Stream(Filepath, std::fstream::out);
        if(!Stream.is_open()) return false;
        std::stringstream MemoryStream;
        bool Result = SerializeMemory(Configuration, MemoryStream);
        if(!Result) return false;
        Stream << MemoryStream.rdbuf();
        Stream.close();
        return true;
    }

    bool ApplicationConfigurationSerializer::Deserialize(ApplicationConfiguration& OutConfiguration, const Path& Filepath)
    {
        std::ofstream Stream(Filepath, std::fstream::in);
        if(!Stream.is_open()) return false;

        std::stringstream MemoryStream;
        MemoryStream << Stream.rdbuf();
        const std::string& Content = MemoryStream.str();
        
        nlohmann::json File = nlohmann::json::parse(Content);
        OutConfiguration.AppName = File["Application Name"];
        OutConfiguration.IconPath = Path(File["Window Icon"].get<std::string>());
        OutConfiguration.WindowWidth = File["Window Width"].get<uint32>();
        OutConfiguration.WindowHeight = File["Window Height"].get<uint32>();
        OutConfiguration.StartFullscreen = File["Start Fullscreen"].get<bool>();
        OutConfiguration.WindowResizable = File["Window Resizable"].get<bool>();
        OutConfiguration.ShowGraphicsAPIName = File["Show Graphics API Name"].get<bool>();
        OutConfiguration.ShowConfiguration = File["Show Configuration"].get<bool>();
        OutConfiguration.ShowOSName = File["Show OS Name"].get<bool>();
        OutConfiguration.ShowDeltaTime = File["Show DeltaTime"].get<bool>();
        OutConfiguration.ShowFPS = File["Show FPS"].get<bool>();
        OutConfiguration.WindowTitleUpdateTime = File["Window Title Update Time"].get<float>();
        OutConfiguration.WithEditor = File["With Editor"].get<bool>();
        OutConfiguration.Graphics.BufferType = File["SwapchainBufferType"].get<GraphicsSettings::SwapchainBufferType>();
        MemoryStream.clear();
        Stream.close();
        return true;
    }

    bool ApplicationConfigurationSerializer::SerializeMemory(const ApplicationConfiguration& Configuration, std::stringstream& OutStream)
    {
        nlohmann::json File;
        File["Application Name"] = Configuration.AppName;
        File["Window Icon"] = Configuration.IconPath.string();
        File["Window Width"] = Configuration.WindowWidth;
        File["Window Height"] = Configuration.WindowHeight;
        File["Start Fullscreen"] = Configuration.StartFullscreen;
        File["Window Resizable"] = Configuration.WindowResizable;
        File["Show Graphics API Name"] = Configuration.ShowGraphicsAPIName;
        File["Show Configuration"] = Configuration.ShowConfiguration;
        File["Show OS Name"] = Configuration.ShowOSName;
        File["Show DeltaTime"] = Configuration.ShowDeltaTime;
        File["Show FPS"] = Configuration.ShowFPS;
        File["Window Title Update Time"] = Configuration.WindowTitleUpdateTime;
        File["With Editor"] = Configuration.WithEditor;
        File["SwapchainBufferType"] = Configuration.Graphics.BufferType;
        OutStream.clear();
        OutStream << File.dump(4);
        return true;
    }

    bool ApplicationConfigurationSerializer::DeserializeMemory(const std::stringstream& Stream, ApplicationConfiguration& OutConfiguration)
    {
        const std::string& Content = Stream.str();
        nlohmann::json File = nlohmann::json::parse(Content);
        OutConfiguration.AppName = File["Application Name"];
        OutConfiguration.IconPath = Path(File["Window Icon"].get<std::string>());
        OutConfiguration.WindowWidth = File["Window Width"].get<uint32>();
        OutConfiguration.WindowHeight = File["Window Height"].get<uint32>();
        OutConfiguration.StartFullscreen = File["Start Fullscreen"].get<bool>();
        OutConfiguration.WindowResizable = File["Window Resizable"].get<bool>();
        OutConfiguration.ShowGraphicsAPIName = File["Show Graphics API Name"].get<bool>();
        OutConfiguration.ShowConfiguration = File["Show Configuration"].get<bool>();
        OutConfiguration.ShowOSName = File["Show OS Name"].get<bool>();
        OutConfiguration.ShowDeltaTime = File["Show DeltaTime"].get<bool>();
        OutConfiguration.ShowFPS = File["Show FPS"].get<bool>();
        OutConfiguration.WindowTitleUpdateTime = File["Window Title Update Time"].get<float>();
        OutConfiguration.WithEditor = File["With Editor"].get<bool>();
        OutConfiguration.Graphics.BufferType = File["SwapchainBufferType"].get<GraphicsSettings::SwapchainBufferType>();
        return true;
    }
}
