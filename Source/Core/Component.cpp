#include "Core/Component.h"

#include "GameObject.h"

namespace Hydro
{
    
    Component::Component(GameObject* Owner, std::string Name) : m_Name(std::move(Name)), m_Enabled(true), m_GameObject(Owner)
    {
    }

    Component::~Component()
    {
        OnDestroy();
    }

    const std::string& Component::GetName() const
    {
        return m_Name;
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

    GUID Component::GetGuid() const
    {
        return m_Guid;
    }
}
