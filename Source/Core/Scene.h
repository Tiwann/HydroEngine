#pragma once
#include "LogCategory.h"
#include "SharedPointer.h"
#include "Core/Log.h"
#include "GUID.h"
#include "GameObject.h"

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
        using Iterator = Array<Ref<GameObject>>::Iterator;
        using ConstIterator = Array<Ref<GameObject>>::ConstIterator;
        friend class Physics2D;

        Scene() = default;
        ~Scene() = default;
        void OnInit();
        void OnUpdate(float Delta);
        void OnRender(const Ref<RendererBackend>& Renderer) const;
        void OnDestroy();
        
        template<typename T = GameObject, typename = std::enable_if_t<std::is_base_of_v<GameObject, T>>>
        Ref<T> CreateObject(const std::string& Name)
        {
            const Ref<GameObject> NewObject = CreateRef<T>(Name, this);
            NewObject->OnInit();
            m_GameObjects.Add(NewObject);
            return Cast<T>(NewObject);
        }

        void ForEach(const std::function<void(Ref<GameObject>)>& Delegate) const
        {
            for(const auto& Object : m_GameObjects)
            {
                Delegate(Object);
            }
        }
        Iterator begin() { return m_GameObjects.begin(); }
        Iterator end() { return m_GameObjects.end(); }

        ConstIterator begin() const { return m_GameObjects.begin(); }
        ConstIterator end() const { return m_GameObjects.end(); }
        
        GUID GetGuid() const { return m_Guid; }
        std::string GetName() const { return m_Name; }
        bool DestroyObject(Ref<GameObject>& Object);
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
        Array<Ref<GameObject>> m_GameObjects;
        
        PhysicsWorld2D m_PhysicsWorld2D;
        PhysicsWorld3D m_PhysicsWorld3D;
        Ref<RendererBackend> m_RendererBackend;
    };
}
