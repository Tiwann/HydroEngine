#include "RigidBody2D.h"

#include "Contact2D.h"
#include "Core/Scene.h"
#include "Components/Transform.h"
#include "Core/MulticastDelegate.h"

#include "Core/Physics/PhysicsWorld2D.h"
#include "Core/Physics/PhysicsBody2D.h"
#include "Core/Physics/PhysicsContactInfo2D.h"
#include "Core/Physics/PhysicsShape.h"

namespace Hydro
{
    RigidBody2D::RigidBody2D(Entity* Owner, const std::string& Name) : PhysicsComponentInterface(Owner, Name){ }
    
    void RigidBody2D::OnInit()
    {
        Component::OnInit();
        
        Scene& Scene = m_Entity->GetScene();
        PhysicsWorld2D& World = Scene.GetPhysicsWorld2D();

        const Ref<Transform> Transform = GetTransform();
        const Vector3 Position = Transform->GetPosition();
        const Vector3 Rotation = Transform->GetRotation();
        
        const PhysicsBodyDefinition Definition { Position, Rotation, PhysicsBodyType::Static, false };
        m_PhysicsBody = World.CreateBody(Definition, PhysicsMaterial());
        m_PhysicsBody->SetGravityScale(1);
        m_PhysicsShape = CreateShape(Transform);
        m_PhysicsBody->CreatePhysicsState(m_PhysicsShape, PhysicsMaterial());
        
        m_PhysicsBody->OnContactBeginEvent.BindMember(this, &RigidBody2D::OnContactBegin);
        m_PhysicsBody->OnContactStayEvent.BindMember(this, &RigidBody2D::OnContactStay);
        m_PhysicsBody->OnContactEndEvent.BindMember(this, &RigidBody2D::OnContactEnd);
    }

    void RigidBody2D::OnStart()
    {
        PhysicsComponentInterface::OnStart();
        const auto& Transform = GetTransform();
        const auto& Position = Transform->GetPosition();
        const auto& Rotation = Transform->GetRotation();
        m_PhysicsBody->SetPositionAndRotation(Position, Rotation);
    }

    void RigidBody2D::OnDestroy()
    {
        Scene& Scene = m_Entity->GetScene();
        PhysicsWorld2D& World = Scene.GetPhysicsWorld2D();

        m_PhysicsBody->OnContactBeginEvent.ClearAll();
        m_PhysicsBody->OnContactStayEvent.ClearAll();
        m_PhysicsBody->OnContactEndEvent.ClearAll();

        delete m_PhysicsShape;
        m_PhysicsBody->DestroyPhysicsState();
        World.DestroyBody(m_PhysicsBody);
    }
    
    void RigidBody2D::OnPhysicsUpdate(f32 Delta)
    {
        const Ref<Transform> Transform = GetTransform();
        const Vector3 NewPosition = m_PhysicsBody->GetPosition();
        const Vector3 NewRotation = m_PhysicsBody->GetRotation();
        Transform->SetPosition(NewPosition);
        Transform->SetRotation(NewRotation);
    }

    void RigidBody2D::OnContactBegin(const PhysicsContactInfo2D& ContactInfo)
    {
        Contact2D Contact;
        Contact.ImpactPoint = ContactInfo.Point;
        Contact.Normal = ContactInfo.Normal;
        OnContactBeginEvent.Broadcast(Contact);
    }

    void RigidBody2D::OnContactStay(const PhysicsContactInfo2D& ContactInfo)
    {
        Contact2D Contact;
        Contact.ImpactPoint = ContactInfo.Point;
        Contact.Normal = ContactInfo.Normal;
        OnContactStayEvent.Broadcast(Contact);
    }

    void RigidBody2D::OnContactEnd(const PhysicsContactInfo2D& ContactInfo)
    {
        Contact2D Contact;
        Contact.ImpactPoint = ContactInfo.Point;
        Contact.Normal = ContactInfo.Normal;
        OnContactEndEvent.Broadcast(Contact);
    }

    f32 RigidBody2D::GetGravityScale() const
    {
        return m_PhysicsBody->GetGravityScale();
    }

    void RigidBody2D::SetGravityScale(f32 Scale)
    {
        m_PhysicsBody->SetGravityScale(Scale);
    }
    
    void RigidBody2D::SetLinearVelocity(const Vector3& Velocity)
    {
        m_PhysicsBody->SetLinearVelocity(Velocity);
    }

    void RigidBody2D::SetAngularVelocity(const Vector3& AngularVelocity)
    {
        m_PhysicsBody->SetAngularVelocity(AngularVelocity);
    }

    Vector3 RigidBody2D::GetLinearVelocity() const
    {
        return m_PhysicsBody->GetLinearVelocity();
    }

    Vector3 RigidBody2D::GetAngularVelocity() const
    {
        return m_PhysicsBody->GetAngularVelocity();
    }

    void RigidBody2D::SetLinearDamping(f32 LinearDamping)
    {
        m_PhysicsBody->SetLinearDamping(LinearDamping);
    }

    void RigidBody2D::SetAngularDamping(f32 AngularDamping)
    {
        m_PhysicsBody->SetAngularDamping(AngularDamping);
    }

    f32 RigidBody2D::GetLinearDamping() const
    {
        return m_PhysicsBody->GetLinearDamping();
    }

    f32 RigidBody2D::GetAngularDamping() const
    {
        return m_PhysicsBody->GetAngularDamping();
    }

    Vector3 RigidBody2D::GetLinearVelocityPoint(const Vector3& Point) const
    {
        return m_PhysicsBody->GetLinearVelocityPoint(Point);
    }

    void RigidBody2D::AddForce(const Vector3& Force)
    {
        m_PhysicsBody->AddForce(Force);
    }

    void RigidBody2D::AddImpulse(const Vector3& Force)
    {
        m_PhysicsBody->AddImpulse(Force);
    }

    void RigidBody2D::AddForceAtPosition(const Vector3& Position, const Vector3& Force)
    {
        m_PhysicsBody->AddForceAtPosition(Position, Force);
    }

    void RigidBody2D::AddImpulseAtPosition(const Vector3& Position, const Vector3& Force)
    {
        m_PhysicsBody->AddImpulseAtPosition(Position, Force);
    }

    void RigidBody2D::SetPosition(const Vector3& Position)
    {
        m_PhysicsBody->SetPosition(Position);
    }

    void RigidBody2D::SetRotation(const Vector3& Rotation)
    {
        m_PhysicsBody->SetRotation(Rotation);
    }

    void RigidBody2D::RecreatePhysicsState()
    {
        m_PhysicsBody->DestroyPhysicsState();
        m_PhysicsBody->CreatePhysicsState(m_PhysicsShape, m_PhysicsBody->GetMaterial());
    }

    const PhysicsMaterial& RigidBody2D::GetMaterial() const
    {
        return m_PhysicsBody->GetMaterial();
    }

    void RigidBody2D::SetMaterial(const PhysicsMaterial& Material)
    {
        m_PhysicsBody->SetMaterial(Material);
    }

    PhysicsConstraintsFlags RigidBody2D::GetConstraints()
    {
        return m_PhysicsBody->GetConstraints();
    }

    void RigidBody2D::SetConstraints(PhysicsConstraintsFlags Constraints)
    {
        m_PhysicsBody->SetConstraints(Constraints);
    }

    bool RigidBody2D::IsSensor() const
    {
        return m_PhysicsBody->IsSensor();
    }

    void RigidBody2D::SetSensor(bool Sensor)
    {
        m_PhysicsBody->SetIsSensor(Sensor);
    }

    PhysicsBodyType RigidBody2D::GetPhysicsBodyType() const
    {
        return m_PhysicsBody->GetType();
    }

    void RigidBody2D::SetPhysicsBodyType(PhysicsBodyType Type)
    {
        m_PhysicsBody->SetType(Type);
    }
}
