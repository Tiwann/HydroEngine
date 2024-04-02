#pragma once
#include "Core/Component.h"
#include "GUID.h"
#include "Macros.h"
#include "SharedPointer.h"
#include "Log.h"
#include "LogCategory.h"
#include "LogVerbosity.h"

HYDRO_DECLARE_LOG_CATEGORY_STATIC(GameObject, "GameObject")

namespace Hydro
{
    class Component;
    class Transform;
    
    class GameObject
    {
    public:
        friend class Scene;
        GameObject(std::string Name);
        ~GameObject();
        
        static Ref<GameObject> Create(const std::string& Name);
        static bool Destroy(Ref<GameObject>& Object);
        
        void SetName(const std::string& Name);

        template<typename T, typename Traits = std::enable_if_t<std::is_base_of_v<Component, T>>>
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
        
        template<typename T, typename = std::enable_if_t<std::is_base_of_v<Component, T>>, typename... Params>
        Ref<T> AddComponent(Params&&... params)
        {
            Ref<T> NewComponentRef = CreateRef<T>(std::forward<Params>(params)...);
            const Ref<Component> AsComponent = Cast<Component, T>(NewComponentRef);
            AsComponent->m_GameObject = this;
            m_Components.push_back(NewComponentRef);
            AsComponent->OnInit();
            HYDRO_LOG(GameObject, Trace, "Created {} component on GameObject {}", AsComponent->GetName(), m_Name);
            return NewComponentRef;
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
        
        void SetParent(Ref<GameObject> Object);
        bool HasChildren() const;
        Ref<GameObject> GetChild(size_t Index) const;
        
        Ref<Transform> GetTransform() const;

        Scene& GetScene() const;
        const std::string& GetName() const { return m_Name; }
    protected:
        void OnInit() const;
        void OnUpdate(float Delta) const;
        void OnPhysicsUpdate(float Delta) const;
        void OnDestroy() const;
        void SetEnabled(bool Enabled);
    private:
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
