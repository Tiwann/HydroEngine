#include "HydroPCH.h"
#include "ShaderUtils.h"
#include <shaderc/shaderc.hpp>

namespace Hydro
{
    shaderc::CompileOptions Hydro::ShaderUtils::CreateShadercCompileOptions(ShaderSourceLanguage Language)
    {
        shaderc::CompileOptions Options;
        Options.SetSourceLanguage((shaderc_source_language)Language);
        Options.SetTargetEnvironment(shaderc_target_env_opengl, shaderc_env_version_opengl_4_5);
        Options.SetGenerateDebugInfo();
        
#if defined(HYDRO_DEBUG)
        shaderc_optimization_level OptimizationLevel = shaderc_optimization_level_zero;
#elif defined(HYDRO_RELEASE)
        shaderc_optimization_level OptimizationLevel = shaderc_optimization_level_performance;
#endif
        Options.SetOptimizationLevel(OptimizationLevel);
        return Options;
    }
    
}
