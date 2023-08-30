#include "HydroPCH.h"
#include "SceneObject.h"

namespace Hydro
{
    std::string_view SceneObject::GetName() const
    {
        return m_Name;
    }

    Ref<SceneObject> SceneObject::CreateEmpty(const std::string& name = "SceneObject")
    {
        return std::make_shared<SceneObject>();
    }
}
