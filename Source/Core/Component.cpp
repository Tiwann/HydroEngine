#include "HydroPCH.h"
#include "Core/Component.h"

#include "GameObject.h"

namespace Hydro
{
    
    Component::Component(std::string Name) : m_Name(std::move(Name)), m_Enabled(true)
    {
    }

    const std::string& Component::GetName() const
    {
        return m_Name;
    }

    GameObject& Component::GetGameObject()
    {
        return *m_GameObject;
    }

    const GameObject& Component::GetGameObject() const
    {
        return *m_GameObject;
    }

    Ref<Transform> Component::GetTransform() const
    {
        return m_GameObject->GetTransform();
    }

    void Component::SetEnabled(bool Enabled)
    {
        if(m_Enabled == Enabled)
            return;
        m_Enabled = Enabled;
    }
}
