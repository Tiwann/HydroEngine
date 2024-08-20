#pragma once
#include <nlohmann/json.hpp>

namespace Hydro
{
    struct GraphicsSettings
    {
        enum class SwapchainBufferType
        {
            DoubleBuffering = 2,
            TripleBuffering = 3
        };
        
        SwapchainBufferType BufferType = SwapchainBufferType::TripleBuffering;
        static GraphicsSettings DefaultSettings;
    };

    inline std::string SwapchainBufferTypeToString(const GraphicsSettings::SwapchainBufferType& BufferType)
    {
        switch (BufferType)
        {
        case GraphicsSettings::SwapchainBufferType::DoubleBuffering:
            return "DoubleBuffering";
        case GraphicsSettings::SwapchainBufferType::TripleBuffering:
            return "TripleBuffering";
        }
        return "";
    }

    inline GraphicsSettings::SwapchainBufferType SwapchainBufferTypeFromString(const std::string& Str)
    {
        if(Str == "DoubleBuffering")
            return GraphicsSettings::SwapchainBufferType::DoubleBuffering;
        if(Str == "TripleBuffering")
            return GraphicsSettings::SwapchainBufferType::TripleBuffering;
        return GraphicsSettings::SwapchainBufferType::DoubleBuffering;
    }

    inline void to_json(nlohmann::json& j, const GraphicsSettings::SwapchainBufferType& BufferType)
    {
        j = SwapchainBufferTypeToString(BufferType);
    }

    inline void from_json(const nlohmann::json& j, GraphicsSettings::SwapchainBufferType& BufferType)
    {
        const std::string Str = j.get<std::string>();
        BufferType = SwapchainBufferTypeFromString(Str);
    }
}
