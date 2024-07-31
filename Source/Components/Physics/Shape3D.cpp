#include "HydroPCH.h"
#include "Shape3D.h"

#include "Math/Vector3.h"


namespace Hydro
{
    void Shape3D::OnInit()
    {
        PhysicsComponent::OnInit();
        
        
    }

    void Shape3D::SetGravityEnabled(bool Enabled) const
    {
    }

    void Shape3D::SetGravityScale(float Scale)
    {
    }

    void Shape3D::SetLinearVelocity(const Vector3& Velocity) const
    {
    }

    void Shape3D::SetAngularVelocity(float AngularVelocity) const
    {
    }

    void Shape3D::SetLinearDamping(float LinearDamping) const
    {
    }

    void Shape3D::SetAngularDamping(float AngularDamping) const
    {
    }

    float Shape3D::GetGravityScale() const
    {
        return {};
    }

    Vector3 Shape3D::GetLinearVelocity() const
    {
        return {};
    }

    float Shape3D::GetAngularVelocity() const
    {
        return {};
    }

    float Shape3D::GetLinearDamping() const
    {
        return {};
    }

    float Shape3D::GetAngularDamping() const
    {
        return {};
    }

    Vector3 Shape3D::GetLinearVelocityPoint(const Vector3& Point) const
    {
        return {};
    }

    void Shape3D::AddForce(const Vector3& Force)
    {
    }

    void Shape3D::AddImpulse(const Vector3& Force)
    {
    }

    void Shape3D::AddForceAtPosition(const Vector3& Position, const Vector3& Force)
    {
    }

    void Shape3D::AddImpulseAtPosition(const Vector3& Position, const Vector3& Force)
    {
    }
}
