#pragma once
#include "Core/Component.h"
#include "Core/Physics/PhysicsBodyType.h"
#include "Core/Physics/PhysicsConstraints.h"
#include "Core/Physics/PhysicsMaterial.h"
#include "Core/MulticastDelegate.h"
#include "Core/Physics/PhysicsShape.h"

namespace Hydro
{
    class Vector3;
    
    class PhysicsComponent : public Component
    {
    public:
        void OnInspectorGUI(const ImGuiIO& IO) override;

        bool GetShowCollisions() const;
        void SetShowCollisions(bool Enabled);

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
        bool m_ShowCollisions = false;
    };

    template<typename BodyBase, typename ShapeBase, typename CollisionType>
    class PhysicsComponentInterface : public PhysicsComponent
    {
    public:
        using CollisionDelegate = MulticastDelegate<void(const CollisionType&)>;
        CollisionDelegate OnCollisionEnterEvent;
        CollisionDelegate OnCollisionStayEvent;
        CollisionDelegate OnCollisionExitEvent;
        
    protected:
        PhysicsComponentInterface(GameObject* Owner, const std::string& Name = "Physics Component") : PhysicsComponent(Owner, Name){}
        virtual ShapeBase* CreateShape(Ref<Transform> ObjectTransform) = 0;
        virtual void RenderCollisions(const Ref<RendererBackend>& Renderer) const = 0;
        virtual void RecreatePhysicsState() = 0;
        
        virtual const PhysicsMaterial& GetMaterial() const = 0;
        virtual void SetMaterial(const PhysicsMaterial& Material) = 0;
        virtual PhysicsConstraintsFlags GetConstraints() = 0;
        virtual void SetConstraints(PhysicsConstraintsFlags Constraints) = 0;
        virtual bool IsSensor() const = 0;
        virtual void SetSensor(bool Sensor) = 0;
        virtual PhysicsBodyType GetPhysicsBodyType() const = 0;
        virtual void SetPhysicsBodyType(PhysicsBodyType Type) = 0;

        void OnRender(const Ref<RendererBackend>& Renderer) override
        {
            if(m_ShowCollisions)
                RenderCollisions(Renderer);
        }
        
        BodyBase* m_PhysicsBody = nullptr;
        ShapeBase* m_PhysicsShape = nullptr;
    };
}
