#pragma once
#include "LogCategory.h"
#include "SharedPointer.h"
#include "Core/Log.h"
#include "GUID.h"
#include "Entity.h"

#include "Core/Physics/PhysicsWorld2D.h"
#include "Core/Physics/PhysicsWorld3D.h"


HYDRO_DECLARE_LOG_CATEGORY_STATIC(Scene, "SCENE");

namespace Hydro
{
    class RendererBackend;
    class Vector3;
    
    class Scene final
    {
    public:
        using Iterator = Array<Ref<Entity>>::Iterator;
        using ConstIterator = Array<Ref<Entity>>::ConstIterator;
        friend class Physics2D;

        Scene() = default;
        ~Scene() = default;
        void OnInit();
        void OnUpdate(float Delta);
        void OnRender(const Ref<RendererBackend>& Renderer) const;
        void OnDestroy();
        
        template<typename T = Entity, typename = std::enable_if_t<std::is_base_of_v<Entity, T>>>
        Ref<T> CreateEntity(const std::string& Name)
        {
            const Ref<Entity> Entity = CreateRef<T>(Name, this);
            Entity->OnInit();
            m_Entities.Add(Entity);
            return Cast<T>(Entity);
        }

        void ForEach(const std::function<void(Ref<Entity>)>& Delegate) const
        {
            for(const auto& Entity : m_Entities)
            {
                Delegate(Entity);
            }
        }
        Iterator begin() { return m_Entities.begin(); }
        Iterator end() { return m_Entities.end(); }

        ConstIterator begin() const { return m_Entities.begin(); }
        ConstIterator end() const { return m_Entities.end(); }
        
        GUID GetGuid() const { return m_Guid; }
        std::string GetName() const { return m_Name; }
        bool DestroyObject(Ref<Entity>& Entity);
        void SetName(const std::string& Name);

        const PhysicsWorld2D& GetPhysicsWorld2D() const
        {
            return m_PhysicsWorld2D;
        }

        const PhysicsWorld3D& GetPhysicsWorld3D() const
        {
            return m_PhysicsWorld3D;
        }

        PhysicsWorld2D& GetPhysicsWorld2D()
        {
            return m_PhysicsWorld2D;
        }
        
        PhysicsWorld3D& GetPhysicsWorld3D()
        {
            return m_PhysicsWorld3D;
        }

    private:
        GUID m_Guid;
        std::string m_Name;
        Array<Ref<Entity>> m_Entities;
        
        PhysicsWorld2D m_PhysicsWorld2D;
        PhysicsWorld3D m_PhysicsWorld3D;
        Ref<RendererBackend> m_RendererBackend;
        
    };
}
