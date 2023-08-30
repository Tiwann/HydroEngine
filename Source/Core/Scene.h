#pragma once
#include <unordered_map>
#include "Macros.h"
#include "SharedPointer.h"
#include "SceneObject.h"

namespace Hydro
{
    class HYDRO_API Scene
    {
    public:
        explicit Scene(std::string name);

        Ref<SceneObject> AddObject(const Ref<SceneObject>& object);
        Ref<SceneObject> AddNew();
        
    private:
        std::string m_Name;
        std::unordered_map<std::string, Ref<SceneObject>> m_SceneObjects;
    };
}
