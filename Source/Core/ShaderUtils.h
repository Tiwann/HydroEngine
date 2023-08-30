#pragma once
#include "Macros.h"
#include "ShaderSourceLanguage.h"

namespace shaderc
{
    class CompileOptions;
}

namespace Hydro
{
    class HYDRO_API ShaderUtils
    {
    public:
        static shaderc::CompileOptions CreateShadercCompileOptions(ShaderSourceLanguage Language);
    };
    
}
