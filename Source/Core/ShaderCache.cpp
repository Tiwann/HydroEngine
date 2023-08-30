#include "HydroPCH.h"
#include "ShaderCache.h"
#include "Filesystem.h"
#include "Log.h"
#include "spdlog/fmt/fmt.h"
#include <fstream>
#include <shaderc/shaderc.h>

#include "LogVerbosity.h"
#include "Core/Shader.h"

namespace Hydro
{
    Ref<ShaderCache> ShaderCache::s_Instance = nullptr;
    
    bool ShaderCache::CacheShaderSpirv(const Shader& Shader, const SPIRVCode& SpirvCode, shaderc_shader_kind ShaderType)
    {
        ShaderCache& Cache = Get();
        const std::string ShaderTypeExtension = ShaderType == shaderc_vertex_shader ? "vert" : "frag";
        const std::string ShaderFilepath = fmt::format("{}.{}", Shader.GetFilename(), ShaderTypeExtension);
        Cache.m_Data.insert(std::make_pair(ShaderFilepath, SpirvCode));

        if(!Directory::Exists(HYDRO_SHADER_CACHE_DIRECTORY))
        {
            Directory::MakeDirectory(HYDRO_SHADER_CACHE_DIRECTORY);
        }
        
        const Path CacheFilepath = fmt::format("{}{}.spv", HYDRO_SHADER_CACHE_DIRECTORY, ShaderFilepath);
        std::ofstream stream(CacheFilepath, std::ios::out | std::ios::binary);
        if(!stream.is_open())
        {
            HYDRO_LOG(ShaderCache, Error, "Failed to cache shader {}: Stream failed to open.", CacheFilepath.string().c_str());
            return false;
        }
        
        stream.write((const char*)SpirvCode.data(), SpirvCode.size() * sizeof(uint32_t));
        stream.close();
        return true;
    }

    const SPIRVCode& ShaderCache::GetCachedShaderByteCode(const Path& Filepath)
    {
        ShaderCache& Cache = Get();
        return Cache.m_Data.at(Filepath);
    }

    ShaderCache& ShaderCache::Get()
    {
        if(!s_Instance)
        {
            static ShaderCache Instance;
            s_Instance = CreateRef<ShaderCache>(Instance);
            return Instance;
        }

        return *s_Instance;
    }
}

