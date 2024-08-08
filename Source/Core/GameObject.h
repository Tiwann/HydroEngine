#pragma once
#include "Core/Component.h"
#include "GUID.h"
#include "SharedPointer.h"
#include "Log.h"
#include "LogCategory.h"
#include "LogVerbosity.h"
#include "MulticastDelegate.h"

HYDRO_DECLARE_LOG_CATEGORY_STATIC(GameObject, "GameObject")

namespace Hydro
{
    class Component;
    class Transform;
    class RendererBackend;
    class Vector3;
    
    class GameObject : public std::enable_shared_from_this<GameObject>
    {
        using ComponentIterator = std::vector<Ref<Component>>::iterator;
        using ComponentConstIterator = std::vector<Ref<Component>>::const_iterator;
    public:
        friend class Scene;
        friend class Application;
        GameObject(std::string Name, Scene* Owner);
        ~GameObject();
        
        static bool Destroy(Ref<GameObject>& Object);
        
        void SetName(const std::string& Name);

        template<typename T>
        Ref<T> GetComponent() const
        {
            for(Ref<Component> Component : m_Components)
            {
                if(Ref<T> CastedComponent = Cast<T>(Component))
                    return CastedComponent;
            }
            return nullptr;
        }

        template<typename T, typename Traits = std::enable_if_t<std::is_base_of_v<Component, T>>>
        Ref<T> GetComponentInChildren() const
        {
            for(const auto& Child : m_Children)
            {
                return Child->GetComponent<T, Traits>();
            }
            return nullptr;
        }
        
        template<typename T>
        Ref<T> AddComponent()
        {
            Ref<T> NewComponent = CreateRef<T>(this);
            const Ref<Component> AsComponent = Cast<Component, T>(NewComponent);
            m_Components.push_back(NewComponent);
            NewComponent->OnInit();
            HYDRO_LOG(GameObject, Verbosity::Trace, "Created {} component on GameObject {}", AsComponent->GetName(), m_Name);
            return NewComponent;
        }
        
        template<typename T, typename = std::enable_if_t<std::is_base_of_v<Component, T>>>
        bool RemoveComponent()
        {
            for(Ref<Component> Component : m_Components)
            {
                if(Ref<T> CastedComponent = Cast<T>(Component))
                {
                    CastedComponent->OnDestroy();
                    m_Components.erase(std::ranges::find(m_Components, Component));
                    Component.reset();
                    return true;
                }
            }
            return false;
        }
        
        void SetParent(const Ref<GameObject>& Object);
        bool HasChildren() const;
        bool HasParent() const;
        
        Ref<GameObject> GetChild(size_t Index) const;
        Ref<GameObject> GetParent() const;
        Ref<Transform> GetTransform() const;

        const Scene& GetScene() const;
        const std::string& GetName() const { return m_Name; }

        
        ComponentIterator begin() { return m_Components.begin(); }
        ComponentIterator end() { return m_Components.end(); }
        ComponentConstIterator begin() const { return m_Components.begin(); }
        ComponentConstIterator end() const { return m_Components.end(); }

        void ForEach(const std::function<void(Ref<Component>)>& Delegate) const
        {
            for(const auto& Component : m_Components)
            {
                Delegate(Component);
            }
        }

        GUID GetGuid() const { return m_Guid; }
    protected:
        virtual void OnInit();
        virtual void OnStart();
        virtual void OnUpdate(float Delta);
        virtual void OnRender(const Ref<RendererBackend>& Renderer);
        virtual void OnPhysicsUpdate(float Delta);
        virtual void OnDestroy();
        void SetEnabled(bool Enabled);

        GUID m_Guid;
        std::string m_Name;
        std::vector<Ref<Component>> m_Components;
        bool m_Enabled;
        std::vector<Ref<GameObject>> m_Children;
        Ref<GameObject> m_Parent;
        Ref<Transform> m_Transform;
        Scene* m_Scene;
    };
}
