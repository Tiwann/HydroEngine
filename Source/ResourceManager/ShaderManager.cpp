#include "HydroPCH.h"
#include "ShaderManager.h"
#include "Core/LogVerbosity.h"
#include "Core/Log.h"

namespace Hydro
{
    Ref<Shader> ShaderManager::Load(const String& Name, const Path& Filepath)
    {
        Ref<Shader> LoadedShader = Shader::Create(*Name, Filepath, ShaderSourceLanguage::GLSL);
        if(!LoadedShader) return nullptr;
        
        if(!LoadedShader->Compile())
        {
            LoadedShader.reset();
            return nullptr;
        }
        

        if(!LoadedShader->Link())
        {
            LoadedShader.reset();
            return nullptr;
        }

        if(!LoadedShader->Validate())
        {
            LoadedShader.reset();
            return nullptr;
        }
        
        m_Data[Name] = LoadedShader;
        return LoadedShader;
    }

    Ref<Shader> ShaderManager::Retrieve(const String& Name)
    {
        if(!m_Data.Contains(Name))
        {
            HYDRO_LOG(ShaderManager, Verbosity::Warning, "Shader \"{}\" not found!", Name);
            return nullptr;
        }
        return m_Data[Name];
    }

    void ShaderManager::ReloadAll()
    {
        for(auto& [Name, Shader] : m_Data)
        {
            Shader->Reload();
        }
    }
}
