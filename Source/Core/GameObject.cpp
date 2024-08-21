#include "HydroPCH.h"
#include "GameObject.h"

#include "Application.h"
#include "Scene.h"
#include "Components/Transform.h"
#include "Components/Rendering/Renderer.h"

namespace Hydro
{
    GameObject::GameObject(std::string Name, Scene* Owner) : m_Name(std::move(Name)), m_Scene(Owner)
    {
        m_Transform = AddComponent<Transform>();
    }

    GameObject::~GameObject()
    {
        
    }

    bool GameObject::Destroy(Ref<GameObject>& Object)
    {
        Application& Application = Application::GetCurrentApplication();
        return Application.GetScene()->DestroyObject(Object);
    }

    void GameObject::SetName(const std::string& Name)
    {
        m_Name = Name;
    }
    
    void GameObject::SetParent(const Ref<GameObject>& Object)
    {
        if(!Object)
        {
            m_Parent = nullptr;
            Object->m_Children.erase(std::ranges::find(m_Children, Object));
            return;
        }

        m_Parent = Object;
        Object->m_Children.push_back(shared_from_this());
    }
    
    bool GameObject::HasChildren() const { return !m_Children.empty(); }

    bool GameObject::HasParent() const
    {
        return m_Parent != nullptr;
    }

    Ref<GameObject> GameObject::GetChild(size_t Index) const
    {
        if(Index < 0 || Index > m_Children.size())
            return nullptr;
        return m_Children[Index];
    }

    Ref<GameObject> GameObject::GetParent() const
    {
        return m_Parent;
    }

    Ref<Transform> GameObject::GetTransform() const
    {
        return m_Transform;
    }

    const Scene& GameObject::GetScene() const
    {
        return *m_Scene;
    }

    Scene& GameObject::GetScene()
    {
        return *m_Scene;
    }


    void GameObject::OnInit()
    {
        ForEach([](const auto& Component){ Component->OnInit(); });
    }

    void GameObject::OnStart()
    {
        ForEach([](const auto& Component) { Component->OnStart(); });
    }

    void GameObject::OnUpdate(float Delta)
    {
        if(!m_Enabled) return;
        for(const Ref<Component>& Component : m_Components)
        {
            if(!Component->m_Enabled)
                continue;
            Component->OnUpdate(Delta);
        }
    }

    void GameObject::OnRender(const Ref<RendererBackend>& Renderer)
    {
        if(!m_Enabled) return;
        for(const Ref<Component>& Component : m_Components)
        {
            if(!Component->m_Enabled)
                continue;
            
            Component->OnRender(Renderer);
        }
    }

    void GameObject::OnPhysicsUpdate(float Delta)
    {
        if(!m_Enabled) return;
        for(const Ref<Component>& Component : m_Components)
        {
            if(!Component->m_Enabled)
                continue;
            Component->OnPhysicsUpdate(Delta);
        }
    }

    void GameObject::OnDestroy()
    {
        for(Ref<Component>& Component : m_Components)
        {
            Component->OnDestroy();
        }
    }

    void GameObject::SetEnabled(bool Enabled)
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
