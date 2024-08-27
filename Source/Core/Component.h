#pragma once
#include "Macros.h"
#include <string>

#include "SharedPointer.h"
#include "Core/GUID.h"
#include "Platform/PlatformImGui.h"


namespace Hydro
{
    class Transform;
    class Entity;
    class RendererBackend;
    
    class Component
    {
    public:
        friend Entity;
        HYDRO_NOT_COPYABLE_NOT_MOVABLE(Component);
        
        Component(Entity* Owner, std::string Name);
        virtual ~Component();

        const std::string& GetName() const;

        Ref<Transform> GetTransform() const;
        
        virtual void OnInit(){}
        virtual void OnStart(){}
        virtual void OnDestroy()
        {
            m_Entity = nullptr;
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
        Entity* m_Entity{nullptr};
    };
}
