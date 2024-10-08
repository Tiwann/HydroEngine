﻿#pragma once
#include "Core/Component.h"
#include "GUID.h"
#include "SharedPointer.h"
#include "Log.h"
#include "LogCategory.h"
#include "LogVerbosity.h"
#include "Core/Containers/Function.h"
#include "Core/Containers/String.h"
#include "Core/Containers/StringFormat.h"

HYDRO_DECLARE_LOG_CATEGORY_STATIC(Entity, "Entity")

namespace Hydro
{
    class Component;
    class Transform;
    class RendererBackend;
    class Vector3;
    
    class Entity : public std::enable_shared_from_this<Entity>
    {
    public:
        using ComponentArray = Array<Ref<Component>>;
        using Iterator = ComponentArray::Iterator;
        using ConstIterator = ComponentArray::ConstIterator;
        
        friend class Scene;
        friend class Application;
        Entity(String Name, Scene* Owner);
        virtual ~Entity() = default;
        
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

        template<typename T>
        Array<Ref<T>> GetAllComponents() const
        {
            Array<Ref<T>> Result;
            for(Ref<Component> Component : m_Components)
            {
                if(Ref<T> CastedComponent = Cast<T>(Component))
                    Result.Add(CastedComponent);
            }
            return Result;
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
            m_Components.Add(NewComponent);
            NewComponent->OnInit();
            HYDRO_LOG(Entity, Verbosity::Trace, "Created {} component on Entity {}", AsComponent->GetName(), m_Name);
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
                    m_Components.Remove(Component);
                    Component.reset();
                    return true;
                }
            }
            return false;
        }

        bool RemoveComponent(Ref<Component>& Component)
        {
            if(!Component) return false;
            
            Component->OnDestroy();
            m_Components.Remove(Component);
            Component.reset();
            return true;
        }
        
        void SetParent(const Ref<Entity>& Entity);
        bool HasChildren() const;
        bool HasParent() const;
        
        Ref<Entity> GetChild(size_t Index) const;
        Ref<Entity> GetParent() const;
        Ref<Transform> GetTransform() const;

        const Scene& GetScene() const;
        Scene& GetScene();

        void SetName(const String& Name);
        const String& GetName() const { return m_Name; }

        
        Iterator begin() { return m_Components.begin(); }
        Iterator end() { return m_Components.end(); }
        ConstIterator begin() const { return m_Components.begin(); }
        ConstIterator end() const { return m_Components.end(); }

        void ForEach(const Function<void(Ref<Component>)>& Delegate) const
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
        virtual void OnUpdate(f32 Delta);
        virtual void OnRender(const Ref<RendererBackend>& Renderer);
        virtual void OnPhysicsUpdate(f32 Delta);
        virtual void OnDestroy();
        void SetEnabled(bool Enabled);

        GUID m_Guid;
        String m_Name;
        Array<Ref<Component>> m_Components;
        bool m_Enabled;
        Array<Ref<Entity>> m_Children;
        Ref<Entity> m_Parent;
        Ref<Transform> m_Transform;
        Scene* m_Scene;
    };
}
