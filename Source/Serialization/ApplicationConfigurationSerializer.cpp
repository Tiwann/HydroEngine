#include "HydroPCH.h"
#include "ApplicationConfigurationSerializer.h"

#include <yaml-cpp/yaml.h>

namespace Hydro
{
    ApplicationConfigurationSerializer::ApplicationConfigurationSerializer(const Path& Filepath) : Serializer(Filepath)
    {

    }

    bool ApplicationConfigurationSerializer::Serialize(const ApplicationConfiguration& Configuration)
    {
        YAML::Emitter Yaml;
        Yaml << YAML::BeginMap;
        Yaml << YAML::Key << "Application Name" << YAML::Value << Configuration.AppName;
        Yaml << YAML::Key << "Window Width" << YAML::Value << Configuration.WindowWidth;
        Yaml << YAML::Key << "Window Height" << YAML::Value << Configuration.WindowHeight;
        Yaml << YAML::Key << "Start Fullscreen" << YAML::Value << Configuration.StartFullscreen;
        Yaml << YAML::Key << "Window Resizable" << YAML::Value << Configuration.WindowResizable;
        Yaml << YAML::Key << "Show Graphics API Name" << YAML::Value << Configuration.ShowGraphicsAPIName;
        Yaml << YAML::Key << "Show Configuration" << YAML::Value << Configuration.ShowConfiguration;
        Yaml << YAML::Key << "Show OS Name" << YAML::Value << Configuration.ShowOSName;
        Yaml << YAML::Key << "Show DeltaTime" << YAML::Value << Configuration.ShowDeltaTime;
        Yaml << YAML::Key << "Show FPS" << YAML::Value << Configuration.ShowFPS;
        Yaml << YAML::Key << "Window Title Update Time" << YAML::Value << Configuration.WindowTitleUpdateTime;
        SerializeSwapchainBufferType(Yaml, Configuration.Graphics.BufferType);
        Yaml << YAML::EndMap;
        m_Stream << Yaml.c_str();
        return true;
    }

    bool ApplicationConfigurationSerializer::Deserialize(ApplicationConfiguration& OutConfiguration)
    {
        YAML::Node Data = YAML::Load(m_Stream);
        OutConfiguration.AppName = Data["Application Name"].as<std::string>();
        OutConfiguration.WindowWidth = Data["Window Width"].as<uint32_t>();
        OutConfiguration.WindowHeight = Data["Window Height"].as<uint32_t>();
        OutConfiguration.StartFullscreen = Data["Start Fullscreen"].as<bool>();
        OutConfiguration.WindowResizable = Data["Window Resizable"].as<bool>()  ;
        OutConfiguration.ShowGraphicsAPIName = Data["Show Graphics API Name"].as<bool>();
        OutConfiguration.ShowConfiguration = Data["Show Configuration"].as<bool>();
        OutConfiguration.ShowOSName = Data["Show OS Name"].as<bool>();
        OutConfiguration.ShowDeltaTime = Data["Show DeltaTime"].as<bool>();
        OutConfiguration.ShowFPS = Data["Show FPS"].as<bool>();
        OutConfiguration.WindowTitleUpdateTime = Data["Window Title Update Time"].as<float>();

        DeserializeSwapchainBufferType(Data, OutConfiguration.Graphics.BufferType);
        
        return true;
    }

    void ApplicationConfigurationSerializer::SerializeSwapchainBufferType(YAML::Emitter& Yaml, GraphicsSettings::SwapchainBufferType SwapchainBufferType)
    {
        switch (SwapchainBufferType) {
        case GraphicsSettings::DoubleBuffering: Yaml << YAML::Key << "SwapchainBufferType" << YAML::Value << "DoubleBuffering"; break;
        case GraphicsSettings::TripleBuffering: Yaml << YAML::Key << "SwapchainBufferType" << YAML::Value << "TripleBuffering"; break;
        }
    }

    void ApplicationConfigurationSerializer::DeserializeSwapchainBufferType(YAML::Node& Yaml, GraphicsSettings::SwapchainBufferType& OutSwapchainBufferType)
    {
        const std::string Value = Yaml["SwapchainBufferType"].as<std::string>();
        if(Value == "DoubleBuffering") OutSwapchainBufferType = GraphicsSettings::DoubleBuffering;
        if(Value == "TripleBuffering") OutSwapchainBufferType = GraphicsSettings::TripleBuffering;
    }
}
