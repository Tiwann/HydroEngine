#pragma once
#include <shaderc/shaderc.h>

#include "BinaryData.h"
#include "Filesystem.h"
#include "Macros.h"
#include "SharedPointer.h"
#include "Map.h"
#include "SPIRV.h"
#include "LogCategory.h"

HYDRO_DECLARE_LOG_CATEGORY_STATIC(ShaderCache, "SHADERCACHE");

namespace Hydro
{
    class HYDRO_API ShaderCache
    {
    public:
        static bool CacheShaderSpirv(const class Shader& Shader, const SPIRVCode& SpirvCode, shaderc_shader_kind ShaderType);
        static const SPIRVCode& GetCachedShaderByteCode(const Path& Filepath);
    private:
        static ShaderCache& Get();
        static Ref<ShaderCache> s_Instance;

        Map<Path, SPIRVCode> m_Data;
    };
}
