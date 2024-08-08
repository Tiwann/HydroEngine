#pragma once
#include "Core/SharedPointer.h"

namespace Hydro
{
    class GameObject;
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

        static void Set(void* Object)
        {
            GetInstance().SetData(Object);
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
        

        void SetData(void* Object)
        {
            m_Object = Object;
        }
        

        template<typename T>
        static T* Get()
        {
            void* Obj = GetInstance().m_Object;
            if(!Obj) return nullptr;
            return (T*)Obj;
        }
        
    private:
        void* m_Object;
        Ref<GameObject> m_GameObject;
    };
}
