#include "HydroPCH.h"
#include "RigidBody3D.h"

#include "Core/Scene.h"
#include "Math/Vector3.h"


namespace Hydro
{
    void RigidBody3D::OnInit()
    {
        PhysicsComponentInterface::OnInit();

        Scene& Scene = m_GameObject->GetScene();
        PhysicsWorld3D& World = Scene.GetPhysicsWorld3D();
        
        const Vector3 Position = GetTransform()->GetPosition();
        const Vector3 Rotation = GetTransform()->GetRotation();
        
        const PhysicsBodyDefinition Definition { Position, Rotation, m_Type, m_IsTrigger };
        m_PhysicsBody = World.CreateBody(Definition, m_Material);
        m_PhysicsShape = CreateShape();
        m_PhysicsBody->CreatePhysicsState(m_PhysicsShape, m_Material);
    }

    void RigidBody3D::OnStart()
    {
        PhysicsComponentInterface::OnStart();
    }

    void RigidBody3D::OnPhysicsUpdate(float Delta)
    {
        PhysicsComponentInterface::OnPhysicsUpdate(Delta);
    }

    void RigidBody3D::RecreatePhysicsState()
    {
    }

    void RigidBody3D::SetMaterial(const PhysicsMaterial& Material)
    {
        PhysicsComponentInterface::SetMaterial(Material);
    }

    void RigidBody3D::SetConstraintsFlags(PhysicsConstraintsFlags Constraints)
    {
        PhysicsComponentInterface::SetConstraintsFlags(Constraints);
    }

    void RigidBody3D::SetTrigger(bool IsTrigger)
    {
        PhysicsComponentInterface::SetTrigger(IsTrigger);
    }

    void RigidBody3D::SetPhysicsBodyType(PhysicsBodyType Type)
    {
        PhysicsComponentInterface::SetPhysicsBodyType(Type);
    }
    
    void RigidBody3D::SetGravityScale(float Scale)
    {
    }

    void RigidBody3D::SetLinearVelocity(const Vector3& Velocity)
    {
    }

    void RigidBody3D::SetAngularVelocity(const Vector3& AngularVelocity)
    {
    }

    void RigidBody3D::SetLinearDamping(float LinearDamping)
    {
    }

    void RigidBody3D::SetAngularDamping(float AngularDamping)
    {
    }

    float RigidBody3D::GetGravityScale() const
    {
        return {};
    }

    Vector3 RigidBody3D::GetLinearVelocity() const
    {
        return {};
    }

    Vector3 RigidBody3D::GetAngularVelocity() const
    {
        return {};
    }

    float RigidBody3D::GetLinearDamping() const
    {
        return {};
    }

    float RigidBody3D::GetAngularDamping() const
    {
        return {};
    }

    Vector3 RigidBody3D::GetLinearVelocityPoint(const Vector3& Point) const
    {
        return {};
    }

    void RigidBody3D::AddForce(const Vector3& Force)
    {
    }

    void RigidBody3D::AddImpulse(const Vector3& Force)
    {
    }

    void RigidBody3D::AddForceAtPosition(const Vector3& Position, const Vector3& Force)
    {
    }

    void RigidBody3D::AddImpulseAtPosition(const Vector3& Position, const Vector3& Force)
    {
    }
}
