#include "RigidBody3D.h"

#include "Core/Scene.h"
#include "Math/Vector3.h"


namespace Hydro
{
    void RigidBody3D::OnInit()
    {
        PhysicsComponentInterface::OnInit();

        Scene& Scene = m_Entity->GetScene();
        PhysicsWorld3D& World = Scene.GetPhysicsWorld3D();
        
        const Ref<Transform> Transform = GetTransform();
        const Vector3 Position = Transform->GetPosition();
        const Vector3 Rotation = Transform->GetRotation();
        
        const PhysicsBodyDefinition Definition { Position, Rotation, PhysicsBodyType::Static, false };
        m_PhysicsBody = World.CreateBody(Definition, PhysicsMaterial());
        m_PhysicsShape = CreateShape(Transform);
        m_PhysicsBody->CreatePhysicsState(m_PhysicsShape, PhysicsMaterial());
    }

    void RigidBody3D::OnStart()
    {
        PhysicsComponentInterface::OnStart();
    }

    void RigidBody3D::OnPhysicsUpdate(float Delta)
    {
        PhysicsComponentInterface::OnPhysicsUpdate(Delta);
    }

    void RigidBody3D::SetGravityScale(float Scale)
    {
        m_PhysicsBody->SetGravityScale(Scale);
    }

    void RigidBody3D::SetLinearVelocity(const Vector3& Velocity)
    {
        m_PhysicsBody->SetLinearVelocity(Velocity);
    }

    void RigidBody3D::SetAngularVelocity(const Vector3& AngularVelocity)
    {
        m_PhysicsBody->SetAngularVelocity(AngularVelocity);
    }

    void RigidBody3D::SetLinearDamping(float LinearDamping)
    {
        m_PhysicsBody->SetLinearDamping(LinearDamping);
    }

    void RigidBody3D::SetAngularDamping(float AngularDamping)
    {
        m_PhysicsBody->SetAngularDamping(AngularDamping);
    }

    float RigidBody3D::GetGravityScale() const
    {
        return m_PhysicsBody->GetGravityScale();
    }

    Vector3 RigidBody3D::GetLinearVelocity() const
    {
        return m_PhysicsBody->GetLinearVelocity();
    }

    Vector3 RigidBody3D::GetLinearVelocityPoint(const Vector3& Point) const
    {
        return m_PhysicsBody->GetLinearVelocityPoint(Point);
    }

    Vector3 RigidBody3D::GetAngularVelocity() const
    {
        return m_PhysicsBody->GetAngularVelocity();
    }

    float RigidBody3D::GetLinearDamping() const
    {
        return m_PhysicsBody->GetLinearDamping();
    }

    float RigidBody3D::GetAngularDamping() const
    {
        return m_PhysicsBody->GetAngularDamping();
    }
    
    void RigidBody3D::AddForce(const Vector3& Force)
    {
        m_PhysicsBody->AddForce(Force);
    }

    void RigidBody3D::AddImpulse(const Vector3& Force)
    {
        m_PhysicsBody->AddImpulse(Force);
    }

    void RigidBody3D::AddForceAtPosition(const Vector3& Position, const Vector3& Force)
    {
        m_PhysicsBody->AddForceAtPosition(Position, Force);
    }

    void RigidBody3D::AddImpulseAtPosition(const Vector3& Position, const Vector3& Force)
    {
        m_PhysicsBody->AddImpulseAtPosition(Position, Force);
    }

    void RigidBody3D::RecreatePhysicsState()
    {
        m_PhysicsBody->DestroyPhysicsState();
        m_PhysicsBody->CreatePhysicsState(m_PhysicsShape, m_PhysicsBody->GetMaterial());
    }

    const PhysicsMaterial& RigidBody3D::GetMaterial() const
    {
        return m_PhysicsBody->GetMaterial();
    }

    void RigidBody3D::SetMaterial(const PhysicsMaterial& Material)
    {
        m_PhysicsBody->SetMaterial(Material);
    }

    PhysicsConstraintsFlags RigidBody3D::GetConstraints()
    {
        return m_PhysicsBody->GetConstraints();
    }

    void RigidBody3D::SetConstraints(PhysicsConstraintsFlags Constraints)
    {
        m_PhysicsBody->SetConstraints(Constraints);
    }

    bool RigidBody3D::IsSensor() const
    {
        return m_PhysicsBody->IsSensor();
    }

    void RigidBody3D::SetSensor(bool Sensor)
    {
        m_PhysicsBody->SetIsSensor(Sensor);
    }

    PhysicsBodyType RigidBody3D::GetPhysicsBodyType() const
    {
        return m_PhysicsBody->GetType();
    }

    void RigidBody3D::SetPhysicsBodyType(PhysicsBodyType Type)
    {
        m_PhysicsBody->SetType(Type);
    }
}
