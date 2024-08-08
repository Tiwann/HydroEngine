#pragma once
#include "Macros.h"
#include <string>

#include "GameObject.h"
#include "SharedPointer.h"
#include "Core/GUID.h"
#include "Platform/PlatformImGui.h"


namespace Hydro
{
    class Transform;
    class GameObject;
    class RendererBackend;
    
    class Component
    {
    public:
        friend GameObject;
        HYDRO_NOT_COPYABLE_NOT_MOVABLE(Component);
        
        Component(GameObject* Owner, std::string Name);
        virtual ~Component();

        const std::string& GetName() const;

        Ref<Transform> GetTransform() const;
        
        virtual void OnInit(){}
        virtual void OnStart(){}
        virtual void OnDestroy()
        {
            m_GameObject = nullptr;
            m_Enabled = false;
        }
        virtual void OnEnable(){}
        virtual void OnDisable(){}
        virtual void OnUpdate(float Delta){}
        virtual void OnPhysicsUpdate(float Delta){}
        virtual void OnRender(const Ref<RendererBackend>& Renderer){}
        virtual void OnInspectorGUI(const ImGuiIO& IO){}
        void SetEnabled(bool Enabled);

        GUID GetGuid() const;
    protected:
        GUID m_Guid;
        std::string m_Name;
        bool m_Enabled;
        GameObject* m_GameObject{nullptr};
    };
}
