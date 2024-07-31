#pragma once
#include "ColliderType.h"
#include "Constraints.h"
#include "Core/Component.h"
#include "Core/PhysicsMaterial.h"
#include "Core/Flags.h"
#include "Core/MulticastDelegate.h"
namespace Hydro
{
    class Vector3;

    template<typename CollisionType>
    class ICollisionResponse
    {
        using CollisionDelegate = MulticastDelegate<void(const CollisionType&)>;
    public:
        virtual ~ICollisionResponse()
        {
            ClearEvents();
        }
        
        CollisionDelegate OnCollisionEnterEvent;
        CollisionDelegate OnCollisionStayEvent;
        CollisionDelegate OnCollisionExitEvent;
        
        virtual void OnCollisionEnter(const CollisionType& Collision){}
        virtual void OnCollisionStay(const CollisionType& Collision){}
        virtual void OnCollisionExit(const CollisionType& Collision){}
        
        void ClearEvents()
        {
            OnCollisionEnterEvent.ClearAll();
            OnCollisionStayEvent.ClearAll();
            OnCollisionExitEvent.ClearAll();
        }
    };
    
    class PhysicsComponent : public Component
    {
    public:
        bool GetShowCollisions() const { return m_ShowCollisions; }

        void SetShowCollisions(bool Enabled)
        {
            m_ShowCollisions = Enabled;
        }

        virtual void SetGravityEnabled(bool Enabled) const = 0;
        virtual void SetGravityScale(float Scale) = 0;
        virtual void SetLinearVelocity(const Vector3& Velocity) const = 0;
        virtual void SetAngularVelocity(float AngularVelocity) const = 0;
        virtual void SetLinearDamping(float LinearDamping) const = 0;
        virtual void SetAngularDamping(float AngularDamping) const = 0;

        virtual float GetGravityScale() const = 0;
        virtual Vector3 GetLinearVelocity() const = 0;
        virtual float GetAngularVelocity() const = 0;
        virtual float GetLinearDamping() const = 0;
        virtual float GetAngularDamping() const = 0;
        virtual Vector3 GetLinearVelocityPoint(const Vector3& Point) const = 0;

        virtual void AddForce(const Vector3& Force) = 0;
        virtual void AddImpulse(const Vector3& Force) = 0;
        virtual void AddForceAtPosition(const Vector3& Position, const Vector3& Force) = 0;
        virtual void AddImpulseAtPosition(const Vector3& Position, const Vector3& Force) = 0;

        PhysicsMaterial GetMaterial() const
        {
            return m_Material;
        }

        virtual void SetMaterial(const PhysicsMaterial& Material)
        {
            m_Material = Material;
        }

        PhysicsConstraintsFlags GetConstraintsFlags() const
        {
            return m_ConstraintsFlags;
        }

        virtual void SetConstraintsFlags(PhysicsConstraintsFlags Constraints)
        {
            m_ConstraintsFlags = Constraints;
        }

        bool IsTrigger() const
        {
            return m_IsTrigger;
        }

        virtual void SetTrigger(bool IsTrigger)
        {
            m_IsTrigger = IsTrigger;
        }

        ColliderType GetType() const
        {
            return m_Type;
        }

        virtual void SetType(ColliderType Type)
        {
            m_Type = Type;
        }
    

    protected:
        virtual void RenderCollisions(const Ref<RendererBackend>& Renderer) const = 0;
    protected:
        PhysicsComponent(GameObject* Owner, const std::string& Name = "Physics Component") : Component(Owner, Name)
        {
            
        }

        void OnRender(const Ref<RendererBackend>& Renderer) override
        {
            if(m_ShowCollisions)
                RenderCollisions(Renderer);
        }
        
        ColliderType m_Type{ColliderType::Static};
        PhysicsMaterial m_Material;
        PhysicsConstraintsFlags m_ConstraintsFlags;
        bool m_IsTrigger{false};
        bool m_ShowCollisions = false;
    };
    
}
