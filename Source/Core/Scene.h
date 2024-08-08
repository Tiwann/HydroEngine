#pragma once
#include "LogCategory.h"
#include "SharedPointer.h"
#include "Core/Log.h"
#include "GUID.h"
#include "GameObject.h"


HYDRO_DECLARE_LOG_CATEGORY_STATIC(Scene, "SCENE");

class b2World;

namespace JPH
{
    class PhysicsSystem;
}

namespace Hydro
{
    class RendererBackend;
    class Vector3;
    
    class Scene
    {
    public:
        using GameObjectIterator = std::vector<Ref<GameObject>>::iterator;
        using GameObjectConstIterator = std::vector<Ref<GameObject>>::const_iterator;
        friend class Physics2D;
        Scene();
        ~Scene();
        
        void OnInit();
        void OnUpdate(float Delta) const;
        void OnRender(const Ref<RendererBackend>& Renderer) const;
        void OnDestroy();
        
        template<typename T = GameObject, typename = std::enable_if_t<std::is_base_of_v<GameObject, T>>>
        Ref<T> CreateObject(const std::string& Name)
        {
            const Ref<GameObject> NewObject = CreateRef<T>(Name, this);
            NewObject->OnInit();
            m_GameObjects.push_back(NewObject);
            return Cast<T>(NewObject);
        }

        void ForEach(const std::function<void(Ref<GameObject>)>& Delegate) const
        {
            for(const auto& Object : m_GameObjects)
            {
                Delegate(Object);
            }
        }
        GameObjectIterator begin() { return m_GameObjects.begin(); }
        GameObjectIterator end() { return m_GameObjects.end(); }

        GameObjectConstIterator begin() const { return m_GameObjects.begin(); }
        GameObjectConstIterator end() const { return m_GameObjects.end(); }
        
        GUID GetGuid() const { return m_Guid; }
        std::string GetName() const { return m_Name; }
        bool DestroyObject(Ref<GameObject>& Object);
        void SetName(const std::string& Name);
    private:
        friend class Shape2D;
        GUID m_Guid;
        std::string m_Name;
        std::vector<Ref<GameObject>> m_GameObjects;
        
        bool m_Enabled;
        b2World* m_Physics2DWorld;
        JPH::PhysicsSystem* m_Physics3DWorld;
        Ref<RendererBackend> m_RendererBackend;
    };
}
