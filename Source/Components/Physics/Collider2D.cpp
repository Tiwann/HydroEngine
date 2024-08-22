#include "HydroPCH.h"
#include "Collider2D.h"
#include "Core/Scene.h"
#include "Components/Transform.h"
#include "Core/MulticastDelegate.h"
#include "Core/Shape2DContactListener.h"

#include "Core/Physics/PhysicsWorld2D.h"
#include "Core/Physics/PhysicsBody2D.h"

namespace Hydro
{
    Collider2D::Collider2D(GameObject* Owner, const std::string& Name) : PhysicsComponent(Owner, Name)
    {
        HYDRO_BIND_EVENT_AS(OnCollisionEnterEvent, ICollisionResponse, &Collider2D::OnCollisionEnter);
        HYDRO_BIND_EVENT_AS(OnCollisionStayEvent, ICollisionResponse, &Collider2D::OnCollisionStay);
        HYDRO_BIND_EVENT_AS(OnCollisionExitEvent, ICollisionResponse, &Collider2D::OnCollisionExit);
    }
    
    void Collider2D::OnInit()
    {
        Component::OnInit();

        Scene& Scene = m_GameObject->GetScene();
        PhysicsWorld2D& World = Scene.GetPhysicsWorld2D();
        
        const Vector3 Position = GetTransform()->GetPosition();
        const Vector3 Rotation = GetTransform()->GetRotation();
        
        const PhysicsBodyDefinition Definition { Position, Rotation, m_Type, m_IsTrigger };
        m_PhysicsBody = World.CreateBody(Definition, m_Material);
        m_PhysicsShape = CreateShape();
        m_PhysicsBody->CreatePhysicsState(*m_PhysicsShape, m_Material);
    }

    void Collider2D::OnStart()
    {
        PhysicsComponent::OnStart();
        const auto& Transform = GetTransform();
        const auto& Position = Transform->GetPosition();
        const auto& Rotation = Transform->GetRotation();
        m_PhysicsBody->SetPositionAndRotation(Position, Rotation);
    }

    void Collider2D::OnDestroy()
    {
        Scene& Scene = m_GameObject->GetScene();
        PhysicsWorld2D& World = Scene.GetPhysicsWorld2D();

        Memory::FreeObject(m_PhysicsShape);
        m_PhysicsBody->DestroyPhysicsState();
        World.DestroyBody(m_PhysicsBody);
    }
    
    void Collider2D::OnPhysicsUpdate(float Delta)
    {
        const bool FixRotation = m_ConstraintsFlags.Contains(PhysicsConstraintsBits::RotationZ);
        
        m_Body->SetFixedRotation(FixRotation);
        m_Body->SetType((b2BodyType)m_Type);

        m_Fixture->SetDensity(m_Material.Density);
        m_Fixture->SetFriction(m_Material.Friction);
        m_Fixture->SetRestitution(m_Material.Bounciness);
        m_Fixture->SetSensor(m_IsTrigger);
        
        const Ref<Transform> Transform = GetTransform();
        b2Vec2 NewPosition = m_Body->GetPosition();
        Transform->SetPosition({NewPosition.x, NewPosition.y, Transform->GetPosition().z});
        Transform->SetRotation({0.0f, 0.0f, m_Body->GetAngle()});
    }
    
    float Collider2D::GetGravityScale() const
    {
        return m_Body->GetGravityScale();
    }

    void Collider2D::SetGravityScale(float Scale)
    {
        m_Body->SetGravityScale(Scale);
    }

    void Collider2D::SetGravityEnabled(bool Enabled)
    {
        m_Body->SetGravityScale(Enabled ? 1.0f : 0.0f);
    }

    void Collider2D::SetLinearVelocity(const Vector3& Velocity)
    {
        m_Body->SetLinearVelocity(Vector2(Velocity));
    }

    void Collider2D::SetAngularVelocity(const Vector3& AngularVelocity)
    {
        m_Body->SetAngularVelocity(AngularVelocity);
    }

    Vector3 Collider2D::GetLinearVelocity() const
    {
        return {m_Body->GetLinearVelocity()};
    }

    float Collider2D::GetAngularVelocity() const
    {
        return m_Body->GetAngularVelocity();
    }

    void Collider2D::SetLinearDamping(float LinearDamping)
    {
        m_Body->SetLinearDamping(LinearDamping);
    }

    void Collider2D::SetAngularDamping(float AngularDamping)
    {
        m_Body->SetAngularDamping(AngularDamping);
    }

    float Collider2D::GetLinearDamping() const
    {
        return m_Body->GetLinearDamping();
    }

    float Collider2D::GetAngularDamping() const
    {
        return m_Body->GetAngularDamping();
    }

    Vector3 Collider2D::GetLinearVelocityPoint(const Vector3& Point) const
    {
        return (Vector3)m_Body->GetLinearVelocityFromWorldPoint((Vector2)Point);
    }

    void Collider2D::AddForce(const Vector3& Force)
    {
        m_Body->ApplyForceToCenter((Vector2)Force, true);
    }

    void Collider2D::AddImpulse(const Vector3& Force)
    {
        m_Body->ApplyLinearImpulseToCenter((Vector2)Force, true);
    }

    void Collider2D::AddForceAtPosition(const Vector3& Position, const Vector3& Force)
    {
        m_Body->ApplyForce((Vector2)Force, (Vector2)Position, true);
    }

    void Collider2D::AddImpulseAtPosition(const Vector3& Position, const Vector3& Force)
    {
        m_Body->ApplyLinearImpulse((Vector2)Force, (Vector2)Position, true);
    }

    void Collider2D::SetPosition(const Vector3& Position) const
    {
        m_Body->SetTransform((Vector2)Position, m_Body->GetAngle());
    }

    void Collider2D::SetRotation(float Rotation) const
    {
        m_Body->SetTransform(m_Body->GetPosition(), Rotation);
    }

    void Collider2D::SetMaterial(const PhysicsMaterial& Material)
    {
        PhysicsComponent::SetMaterial(Material);
        RecreatePhysicsState();
    }

    void Collider2D::SetConstraintsFlags(Flags<PhysicsConstraintsBits> Constraints)
    {
        PhysicsComponent::SetConstraintsFlags(Constraints);
        RecreatePhysicsState();
    }

    void Collider2D::SetTrigger(bool IsTrigger)
    {
        PhysicsComponent::SetTrigger(IsTrigger);
        RecreatePhysicsState();
    }

    void Collider2D::SetPhysicsBodyType(PhysicsBodyType Type)
    {
        PhysicsComponent::SetPhysicsBodyType(Type);
        RecreatePhysicsState();
    }

    void Collider2D::RecreatePhysicsState()
    {
        m_Body->DestroyFixture(m_Fixture);
        delete m_PhysicsShape;
        m_PhysicsShape = CreateShape();

        b2FixtureDef FixtureDef{};
        FixtureDef.shape = m_PhysicsShape;
        FixtureDef.density = m_Material.Density;
        FixtureDef.friction = m_Material.Friction;
        FixtureDef.restitution = m_Material.Bounciness;
        FixtureDef.isSensor = m_IsTrigger;

        b2FixtureUserData FixtureUserData;
        FixtureUserData.pointer = (uintptr_t)this;
        FixtureDef.userData = FixtureUserData;
        m_Fixture = m_Body->CreateFixture(&FixtureDef);
    }
}
