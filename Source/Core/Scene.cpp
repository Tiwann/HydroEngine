#include "HydroPCH.h"
#include "Scene.h"

namespace Hydro
{
    Scene::Scene(std::string name) : m_Name(std::move(name))
    {  
    }

    Ref<SceneObject> Scene::AddObject(const Ref<SceneObject>& object)
    {
        m_SceneObjects.emplace(object->GetName(), object);
        return object;
    }

    Ref<SceneObject> Scene::AddNew()
    {
        Ref<SceneObject> object = CreateRef<SceneObject>();
        m_SceneObjects.emplace(object->GetName(), object);
        return object;
    }
}
