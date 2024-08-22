#pragma once
#include "Core/Physics/PhysicsBody.h"

namespace JPH { class Body; class Shape; }

namespace Hydro
{
    class PhysicsShape3D;
    class PhysicsWorld3D;
    
    class PhysicsBody3D : public PhysicsBody<PhysicsShape3D, PhysicsWorld3D>
    {
    public:
        PhysicsBody3D(uintptr_t Handle, PhysicsWorld3D& World) : PhysicsBody(Handle, World) { }
        
        void SetUserPointer(void* User) override;
        void* GetUserPointer() const override;

        void CreatePhysicsState(const PhysicsShape3D& Shape, const PhysicsMaterial& Material) override;
        void DestroyPhysicsState() override;
        void SetMaterial(const PhysicsMaterial& Material) override;

        void SetPosition(const Vector3& Position) override;
        Vector3 GetPosition() const override;
        void SetRotation(const Vector3& Rotation) override;
        Vector3 GetRotation() const override;
        void SetPositionAndRotation(const Vector3& Position, const Vector3& Rotation) override;

        void SetGravityScale(float Scale) override;
        void SetLinearVelocity(const Vector3& Velocity) override;
        void SetAngularVelocity(const Vector3& AngularVelocity) override;
        void SetLinearDamping(float LinearDamping) override;
        void SetAngularDamping(float AngularDamping) override;
        
        float GetGravityScale() const override;
        Vector3 GetLinearVelocity() const override;
        Vector3 GetLinearVelocityPoint(const Vector3& Point) const override;
        Vector3 GetAngularVelocity() const override;
        float GetLinearDamping() const override;
        float GetAngularDamping() const override;
        
        void AddForce(const Vector3& Force) override;
        void AddImpulse(const Vector3& Force) override;
        void AddForceAtPosition(const Vector3& Position, const Vector3& Force) override;
        void AddImpulseAtPosition(const Vector3& Position, const Vector3& Force) override;
    private :
        JPH::Shape* m_Shape = nullptr;
    };
}
