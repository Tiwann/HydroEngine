#include "HydroPCH.h"
#include "GameObject.h"

#include "Application.h"
#include "Scene.h"
#include "Components/Transform.h"

namespace Hydro
{
    GameObject::GameObject(std::string Name) : m_Name(std::move(Name))
    {
        m_Transform = AddComponent<Transform>();
    }

    GameObject::~GameObject()
    {
        OnDestroy();
    }

    Ref<GameObject> GameObject::Create(const std::string& Name)
    {
        const Application& Application = Application::GetCurrentApplication();
        Ref<GameObject> NewObject = Application.GetScene().CreateObject(Name);
        return NewObject;
    }

    bool GameObject::Destroy(Ref<GameObject>& Object)
    {
        const Application& Application = Application::GetCurrentApplication();
        return Application.GetScene().Destroy(Object);
    }

    void GameObject::SetName(const std::string& Name)
    {
        m_Name = Name;
    }
    
    void GameObject::SetParent(Ref<GameObject> Object)
    {
        if(Object == nullptr)
        {
            Object->m_Parent = nullptr;
        }

        Object->m_Parent = Ref<GameObject>(this);
    }
    
    bool GameObject::HasChildren() const { return !m_Children.empty(); }

    Ref<GameObject> GameObject::GetChild(size_t Index) const
    {
        if(Index < 0 || Index > m_Children.size())
            return nullptr;
        return m_Children[Index];
    }

    Ref<Transform> GameObject::GetTransform() const
    {
        return m_Transform;
    }

    Scene& GameObject::GetScene() const
    {
        return *m_Scene;
    }
    

    void GameObject::OnInit() const
    {
        for(const Ref<Component>& Component : m_Components)
        {
            Component->OnInit();
        }
    }

    void GameObject::OnUpdate(float Delta) const
    {
        if(!m_Enabled) return;
        for(const Ref<Component>& Component : m_Components)
        {
            if(!Component->m_Enabled)
                continue;
            Component->OnUpdate(Delta);
        }
    }

    void GameObject::OnPhysicsUpdate(float Delta) const
    {
        if(!m_Enabled) return;
        for(const Ref<Component>& Component : m_Components)
        {
            if(!Component->m_Enabled)
                continue;
            Component->OnPhysicsUpdate(Delta);
        }
    }

    void GameObject::OnDestroy() const
    {
        for(const Ref<Component>& Component : m_Components)
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
