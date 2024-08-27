#include "Entity.h"

#include "Application.h"
#include "Scene.h"
#include "Components/Transform.h"
#include "Components/Rendering/Renderer.h"

namespace Hydro
{
    Entity::Entity(std::string Name, Scene* Owner) : m_Name(std::move(Name)), m_Scene(Owner)
    {
        m_Transform = AddComponent<Transform>();
    }

    void Entity::SetName(const std::string& Name)
    {
        m_Name = Name;
    }
    
    void Entity::SetParent(const Ref<Entity>& Entity)
    {
        if(!Entity)
        {
            m_Parent = nullptr;
            Entity->m_Children.Remove(Entity);
            return;
        }

        m_Parent = Entity;
        Entity->m_Children.Add(shared_from_this());
    }
    
    bool Entity::HasChildren() const { return !m_Children.IsEmpty(); }

    bool Entity::HasParent() const { return m_Parent != nullptr; }

    Ref<Entity> Entity::GetChild(size_t Index) const
    {
        if(Index < 0 || Index > m_Children.Count())
            return nullptr;
        return m_Children[Index];
    }

    Ref<Entity> Entity::GetParent() const
    {
        return m_Parent;
    }

    Ref<Transform> Entity::GetTransform() const
    {
        return m_Transform;
    }

    const Scene& Entity::GetScene() const
    {
        return *m_Scene;
    }

    Scene& Entity::GetScene()
    {
        return *m_Scene;
    }


    void Entity::OnInit()
    {
        ForEach([](const auto& Component){ Component->OnInit(); });
    }

    void Entity::OnStart()
    {
        ForEach([](const auto& Component) { Component->OnStart(); });
    }

    void Entity::OnUpdate(float Delta)
    {
        if(!m_Enabled) return;
        for(const Ref<Component>& Component : m_Components)
        {
            if(!Component->m_Enabled)
                continue;
            Component->OnUpdate(Delta);
        }
    }

    void Entity::OnRender(const Ref<RendererBackend>& Renderer)
    {
        if(!m_Enabled) return;
        for(const Ref<Component>& Component : m_Components)
        {
            if(!Component->m_Enabled)
                continue;
            
            Component->OnRender(Renderer);
        }
    }

    void Entity::OnPhysicsUpdate(float Delta)
    {
        if(!m_Enabled) return;
        for(const Ref<Component>& Component : m_Components)
        {
            if(!Component->m_Enabled)
                continue;
            Component->OnPhysicsUpdate(Delta);
        }
    }

    void Entity::OnDestroy()
    {
        for(Ref<Component>& Component : m_Components)
        {
            Component->OnDestroy();
        }
    }

    void Entity::SetEnabled(bool Enabled)
    {
        if(m_Enabled == Enabled)
            return;
        
        m_Enabled = Enabled;
        for(const Ref<Component>& Component : m_Components)
        {
            if(m_Enabled)
                Component->OnEnable();
            else
                Component->OnDisable();
        }
    }
}
