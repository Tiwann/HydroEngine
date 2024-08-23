#pragma once
#include "PhysicsComponent.h"

namespace Hydro
{
    struct Collision3D;
    struct PhysicsMaterial;
    class PhysicsBody3D;
    class PhysicsShape3D;
    
    class RigidBody3D : public PhysicsComponentInterface<PhysicsBody3D, PhysicsShape3D, Collision3D>
    {
    public:
        friend class GameObject;
        RigidBody3D(GameObject* Owner, const std::string& Name) : PhysicsComponentInterface(Owner, Name) { }

        void OnInit() override;
        void OnStart() override;
        void OnPhysicsUpdate(float Delta) override;
        
        void SetGravityScale(float Scale) override;
        void SetLinearVelocity(const Vector3& Velocity) override;
        void SetAngularVelocity(const Vector3& AngularVelocity) override;
        void SetLinearDamping(float LinearDamping) override;
        void SetAngularDamping(float AngularDamping) override;
        float GetGravityScale() const override;
        Vector3 GetLinearVelocity() const override;
        Vector3 GetAngularVelocity() const override;
        float GetLinearDamping() const override;
        float GetAngularDamping() const override;
        Vector3 GetLinearVelocityPoint(const Vector3& Point) const override;
        void AddForce(const Vector3& Force) override;
        void AddImpulse(const Vector3& Force) override;
        void AddForceAtPosition(const Vector3& Position, const Vector3& Force) override;
        void AddImpulseAtPosition(const Vector3& Position, const Vector3& Force) override;
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
