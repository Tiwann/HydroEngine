#pragma once
#include "Core/SharedPointer.h"

namespace Hydro
{
    class Entity;
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

        static void SetEntity(const Ref<Entity>& Entity)
        {
            GetInstance().m_Entity = Entity;
        }

        static Ref<Entity> GetEntity()
        {
            if(!GetInstance().m_Entity) return nullptr;
            return GetInstance().m_Entity;
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
        Ref<Entity> m_Entity;
        Ref<Component> m_Component;
    };
}
