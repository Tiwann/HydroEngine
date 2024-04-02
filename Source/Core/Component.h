#pragma once
#include "Macros.h"
#include <string>

#include "GameObject.h"
#include "SharedPointer.h"
#include "Core/GUID.h"

namespace Hydro
{
    class Transform;
    class GameObject;
    
    class Component
    {
    public:
        friend GameObject;
        HYDRO_NO_COPYABLE_NO_MOVABLE(Component);
        


        Component(std::string Name);
        virtual ~Component() = default;

        const std::string& GetName() const;
        GameObject& GetGameObject();
        const GameObject& GetGameObject() const;
        Ref<Transform> GetTransform() const;
        
        virtual void OnInit(){}
        virtual void OnDestroy(){}
        virtual void OnEnable(){}
        virtual void OnDisable(){}
        virtual void OnUpdate(float Delta){}
        virtual void OnPhysicsUpdate(float Delta){}
        void SetEnabled(bool Enabled);
    protected:
        GUID m_Guid;
        std::string m_Name;
        bool m_Enabled;
        GameObject* m_GameObject;
    };
}
