#pragma once
#include "PhysicsComponent.h"


namespace Hydro
{
    class Vector3;
    class Transform;
    struct PhysicsMaterial;
    struct Collision2D;
    class PhysicsBody2D;
    class PhysicsShape2D;
    
    class RigidBody2D : public PhysicsComponentInterface<PhysicsBody2D, PhysicsShape2D>, public ICollisionResponse<Collision2D>
    {
    protected:
        friend class GameObject;
        RigidBody2D(GameObject* Owner, const std::string& Name);
        
        void OnInit() override;
        void OnStart() override;
        void OnDestroy() override;
        void OnPhysicsUpdate(float Delta) override;
    
    public:
        float GetGravityScale() const override;
        void SetGravityScale(float Scale) override;
        void SetLinearVelocity(const Vector3& Velocity) override;
        void SetAngularVelocity(const Vector3& AngularVelocity) override;
        void SetLinearDamping(float LinearDamping) override;
        void SetAngularDamping(float AngularDamping) override;
        
        Vector3 GetLinearVelocity() const override;
        Vector3 GetAngularVelocity() const override;
        float GetLinearDamping() const override;
        float GetAngularDamping() const override;
        Vector3 GetLinearVelocityPoint(const Vector3& Point) const override;
        
        void AddForce(const Vector3& Force) override;
        void AddImpulse(const Vector3& Force) override;
        void AddForceAtPosition(const Vector3& Position, const Vector3& Force) override;
        void AddImpulseAtPosition(const Vector3& Position, const Vector3& Force) override;
        void SetPosition(const Vector3& Position);
        void SetRotation(const Vector3& Rotation);
        void RecreatePhysicsState() override;
        
        const PhysicsMaterial& GetMaterial() const override;
        void SetMaterial(const PhysicsMaterial& Material) override;
        PhysicsConstraintsFlags GetConstraints() override;
        void SetConstraints(PhysicsConstraintsFlags Constraints) override;
        bool IsSensor() const override;
        void SetSensor(bool Sensor) override;
        PhysicsBodyType GetPhysicsBodyType() const override;
        void SetPhysicsBodyType(PhysicsBodyType Type) override;
    };
}
