#include "HydroPCH.h"
#include "Collider3D.h"

#include "Core/Scene.h"
#include "Math/Vector3.h"


namespace Hydro
{
    void Collider3D::OnInit()
    {
        PhysicsComponent::OnInit();

        
    }

    void Collider3D::OnStart()
    {
        PhysicsComponent::OnStart();
    }

    void Collider3D::OnPhysicsUpdate(float Delta)
    {
        PhysicsComponent::OnPhysicsUpdate(Delta);
    }

    void Collider3D::RecreatePhysicsState()
    {
    }

    void Collider3D::SetMaterial(const PhysicsMaterial& Material)
    {
        PhysicsComponent::SetMaterial(Material);
    }

    void Collider3D::SetConstraintsFlags(PhysicsConstraintsFlags Constraints)
    {
        PhysicsComponent::SetConstraintsFlags(Constraints);
    }

    void Collider3D::SetTrigger(bool IsTrigger)
    {
        PhysicsComponent::SetTrigger(IsTrigger);
    }

    void Collider3D::SetPhysicsBodyType(PhysicsBodyType Type)
    {
        PhysicsComponent::SetPhysicsBodyType(Type);
    }

    void Collider3D::SetGravityEnabled(bool Enabled)
    {
    }

    void Collider3D::SetGravityScale(float Scale)
    {
    }

    void Collider3D::SetLinearVelocity(const Vector3& Velocity)
    {
    }

    void Collider3D::SetAngularVelocity(const Vector3& AngularVelocity)
    {
    }

    void Collider3D::SetLinearDamping(float LinearDamping)
    {
    }

    void Collider3D::SetAngularDamping(float AngularDamping)
    {
    }

    float Collider3D::GetGravityScale() const
    {
        return {};
    }

    Vector3 Collider3D::GetLinearVelocity() const
    {
        return {};
    }

    float Collider3D::GetAngularVelocity() const
    {
        return {};
    }

    float Collider3D::GetLinearDamping() const
    {
        return {};
    }

    float Collider3D::GetAngularDamping() const
    {
        return {};
    }

    Vector3 Collider3D::GetLinearVelocityPoint(const Vector3& Point) const
    {
        return {};
    }

    void Collider3D::AddForce(const Vector3& Force)
    {
    }

    void Collider3D::AddImpulse(const Vector3& Force)
    {
    }

    void Collider3D::AddForceAtPosition(const Vector3& Position, const Vector3& Force)
    {
    }

    void Collider3D::AddImpulseAtPosition(const Vector3& Position, const Vector3& Force)
    {
    }
}
