#pragma once
#include "Core/SharedPointer.h"

namespace Hydro
{
    class GameObject;
    class Component;
}

namespace Hydro
{
    class Selection
    {
    public:
        static Selection& GetInstance()
        {
            static Selection instance;
            return instance;
        }

        static void SetGameObject(const Ref<GameObject>& Object)
        {
            GetInstance().m_GameObject = Object;
        }

        static Ref<GameObject> GetGameObject()
        {
            if(!GetInstance().m_GameObject) return nullptr;
            return GetInstance().m_GameObject;
        }

        static void SetComponent(const Ref<Component>& Component)
        {
            GetInstance().m_Component = Component;
        }
        
        static Ref<Component> GetComponent()
        {
            if(!GetInstance().m_Component) return nullptr;
            return GetInstance().m_Component;
        }

        
    private:
        Ref<GameObject> m_GameObject;
        Ref<Component> m_Component;
    };
}
