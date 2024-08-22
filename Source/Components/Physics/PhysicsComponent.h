#pragma once
#include "Core/Physics/PhysicsBodyType.h"
#include "Constraints.h"
#include "Core/Component.h"
#include "Core/Physics/PhysicsMaterial.h"
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
        void OnInspectorGUI(const ImGuiIO& IO) override;

        bool GetShowCollisions() const;
        void SetShowCollisions(bool Enabled);
        PhysicsMaterial GetMaterial() const;
        virtual void SetMaterial(const PhysicsMaterial& Material);
        PhysicsConstraintsFlags GetConstraintsFlags() const;
        virtual void SetConstraintsFlags(PhysicsConstraintsFlags Constraints);
        bool IsTrigger() const;
        virtual void SetTrigger(bool IsTrigger);
        PhysicsBodyType GetType() const;
        virtual void SetPhysicsBodyType(PhysicsBodyType Type);

        virtual void SetGravityScale(float Scale) = 0;
        virtual void SetLinearVelocity(const Vector3& Velocity) = 0;
        virtual void SetAngularVelocity(const Vector3& AngularVelocity) = 0;
        virtual void SetLinearDamping(float LinearDamping) = 0;
        virtual void SetAngularDamping(float AngularDamping) = 0;

        virtual float GetGravityScale() const = 0;
        virtual Vector3 GetLinearVelocity() const = 0;
        virtual Vector3 GetAngularVelocity() const = 0;
        virtual float GetLinearDamping() const = 0;
        virtual float GetAngularDamping() const = 0;
        virtual Vector3 GetLinearVelocityPoint(const Vector3& Point) const = 0;

        virtual void AddForce(const Vector3& Force) = 0;
        virtual void AddImpulse(const Vector3& Force) = 0;
        virtual void AddForceAtPosition(const Vector3& Position, const Vector3& Force) = 0;
        virtual void AddImpulseAtPosition(const Vector3& Position, const Vector3& Force) = 0;

    protected:
        PhysicsComponent(GameObject* Owner, const std::string& Name) : Component(Owner, Name){}
        PhysicsBodyType m_Type = PhysicsBodyType::Static;
        PhysicsMaterial m_Material;
        PhysicsConstraintsFlags m_ConstraintsFlags;
        bool m_IsTrigger = false;
        bool m_ShowCollisions = false;
        bool m_IsColliding = false;
    };

    template<typename BodyBase, typename ShapeBase>
    class PhysicsComponentInterface : public PhysicsComponent
    {
    protected:
        PhysicsComponentInterface(GameObject* Owner, const std::string& Name = "Physics Component") : PhysicsComponent(Owner, Name){}
        virtual ShapeBase* CreateShape() = 0;
        virtual void RenderCollisions(const Ref<RendererBackend>& Renderer) const = 0;
        virtual void RecreatePhysicsState() = 0;


        void OnRender(const Ref<RendererBackend>& Renderer) override
        {
            if(m_ShowCollisions)
                RenderCollisions(Renderer);
        }
        
        BodyBase* m_PhysicsBody = nullptr;
        ShapeBase* m_PhysicsShape = nullptr;
    };
}
