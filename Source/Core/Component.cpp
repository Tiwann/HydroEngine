﻿#include "Core/Component.h"

#include "Entity.h"

namespace Hydro
{
    
    Component::Component(Entity* Owner, std::string Name) : m_Name(std::move(Name)), m_Enabled(true), m_Entity(Owner)
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
        return m_Entity->GetTransform();
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
