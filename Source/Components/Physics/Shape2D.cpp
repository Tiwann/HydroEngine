#include "HydroPCH.h"
#include "Shape2D.h"

#include <box2d/b2_world.h>
#include <box2d/b2_math.h>
#include "Core/Scene.h"
#include "Components/Transform.h"
#include "Collision2D.h"
#include "Core/MulticastDelegate.h"
#include "Core/Shape2DContactListener.h"

namespace Hydro
{
    Shape2D::Shape2D(GameObject* Owner, const std::string& Name) : PhysicsComponent(Owner, Name)
    {
        OnCollisionEnterEvent += HYDRO_BIND(&Shape2D::OnCollisionEnter);
        OnCollisionStayEvent += HYDRO_BIND(&Shape2D::OnCollisionStay);
        OnCollisionExitEvent += HYDRO_BIND(&Shape2D::OnCollisionExit);
        Owner->GetTransform()->OnScaleSet += HYDRO_BIND(&Shape2D::OnTransformScaleSet);
    }
    void Shape2D::OnInit()
    {
        Component::OnInit();

        const Vector3 Position = GetTransform()->GetPosition();
        const Vector3 Rotation = GetTransform()->GetRotation();

        b2BodyDef BodyDef{};
        BodyDef.position = Vector2(Position);
        BodyDef.angle = Math::Radians(Rotation.z);
        BodyDef.type = (b2BodyType)m_Type;

        b2BodyUserData UserData;
        UserData.pointer = (uintptr_t)this;
        BodyDef.userData = UserData;

        b2World* World = m_GameObject->GetScene().m_Physics2DWorld;
        m_Body = World->CreateBody(&BodyDef);

        m_Shape = CreateShape();

        b2FixtureDef FixtureDef{};
        FixtureDef.shape = m_Shape;
        FixtureDef.density = m_Material.Density;
        FixtureDef.friction = m_Material.Friction;
        FixtureDef.restitution = m_Material.Bounciness;
        FixtureDef.isSensor = m_IsTrigger;

        b2FixtureUserData FixtureUserData;
        FixtureUserData.pointer = (uintptr_t)this;
        FixtureDef.userData = FixtureUserData;
        m_Fixture = m_Body->CreateFixture(&FixtureDef);

        m_ContactListener = new Shape2DContactListener;
        World->SetContactListener(m_ContactListener);
    }

    void Shape2D::OnStart()
    {
        PhysicsComponent::OnStart();
        const auto& Transform = GetTransform();
        const auto& Position = GetTransform()->GetPosition();
        m_Body->SetTransform({Position.x, Position.y}, Transform->GetRotation().z);
    }

    void Shape2D::OnDestroy()
    {
        m_Body->DestroyFixture(m_Fixture);
        m_GameObject->GetScene().m_Physics2DWorld->DestroyBody(m_Body);
        delete m_ContactListener;
        delete m_Shape;
    }
    
    void Shape2D::OnPhysicsUpdate(float Delta)
    {
        const bool FixRotation = m_ConstraintsFlags.Contains(PhysicsConstraintsBits::RotationZ);
        
        m_Body->SetFixedRotation(FixRotation);
        m_Body->SetType((b2BodyType)m_Type);

        m_Fixture->SetDensity(m_Material.Density);
        m_Fixture->SetFriction(m_Material.Friction);
        m_Fixture->SetRestitution(m_Material.Bounciness);
        m_Fixture->SetSensor(m_IsTrigger);
        
        const Ref<Transform> Trans = GetTransform();
        b2Vec2 Position = m_Body->GetPosition();
        Trans->SetPosition({Position.x, Position.y, Trans->GetPosition().z});
        Trans->SetRotation({0.0f, 0.0f, m_Body->GetAngle()});
    }
    
    float Shape2D::GetGravityScale() const
    {
        return m_Body->GetGravityScale();
    }

    void Shape2D::SetGravityScale(float Scale)
    {
        m_Body->SetGravityScale(Scale);
    }

    void Shape2D::SetGravityEnabled(bool Enabled) const
    {
        m_Body->SetGravityScale(Enabled ? 1.0f : 0.0f);
    }

    void Shape2D::SetLinearVelocity(const Vector3& Velocity) const
    {
        m_Body->SetLinearVelocity(Vector2(Velocity));
    }

    void Shape2D::SetAngularVelocity(float AngularVelocity) const
    {
        m_Body->SetAngularVelocity(AngularVelocity);
    }

    Vector3 Shape2D::GetLinearVelocity() const
    {
        return Vector2(m_Body->GetLinearVelocity());
    }

    float Shape2D::GetAngularVelocity() const
    {
        return m_Body->GetAngularVelocity();
    }

    void Shape2D::SetLinearDamping(float LinearDamping) const
    {
        m_Body->SetLinearDamping(LinearDamping);
    }

    void Shape2D::SetAngularDamping(float AngularDamping) const
    {
        m_Body->SetAngularDamping(AngularDamping);
    }

    float Shape2D::GetLinearDamping() const
    {
        return m_Body->GetLinearDamping();
    }

    float Shape2D::GetAngularDamping() const
    {
        return m_Body->GetAngularDamping();
    }

    Vector3 Shape2D::GetLinearVelocityPoint(const Vector3& Point) const
    {
        return (Vector3)m_Body->GetLinearVelocityFromWorldPoint((Vector2)Point);
    }

    void Shape2D::AddForce(const Vector3& Force)
    {
        m_Body->ApplyForceToCenter((Vector2)Force, true);
    }

    void Shape2D::AddImpulse(const Vector3& Force)
    {
        m_Body->ApplyLinearImpulseToCenter((Vector2)Force, true);
    }

    void Shape2D::AddForceAtPosition(const Vector3& Position, const Vector3& Force)
    {
        m_Body->ApplyForce((Vector2)Force, (Vector2)Position, true);
    }

    void Shape2D::AddImpulseAtPosition(const Vector3& Position, const Vector3& Force)
    {
        m_Body->ApplyLinearImpulse((Vector2)Force, (Vector2)Position, true);
    }

    void Shape2D::SetPosition(const Vector3& Position) const
    {
        m_Body->SetTransform((Vector2)Position, m_Body->GetAngle());
    }

    void Shape2D::SetMaterial(const PhysicsMaterial& Material)
    {
        PhysicsComponent::SetMaterial(Material);
        RecreateFixture();
    }

    void Shape2D::SetConstraintsFlags(Flags<PhysicsConstraintsBits> Constraints)
    {
        PhysicsComponent::SetConstraintsFlags(Constraints);
        RecreateFixture();
    }

    void Shape2D::SetTrigger(bool IsTrigger)
    {
        PhysicsComponent::SetTrigger(IsTrigger);
        RecreateFixture();
    }

    void Shape2D::SetType(ColliderType Type)
    {
        PhysicsComponent::SetType(Type);
        RecreateFixture();
    }

    void Shape2D::RecreateFixture()
    {
        m_Body->DestroyFixture(m_Fixture);
        delete m_Shape;
        m_Shape = CreateShape();

        b2FixtureDef FixtureDef{};
        FixtureDef.shape = m_Shape;
        FixtureDef.density = m_Material.Density;
        FixtureDef.friction = m_Material.Friction;
        FixtureDef.restitution = m_Material.Bounciness;
        FixtureDef.isSensor = m_IsTrigger;

        b2FixtureUserData FixtureUserData;
        FixtureUserData.pointer = (uintptr_t)this;
        FixtureDef.userData = FixtureUserData;
        m_Fixture = m_Body->CreateFixture(&FixtureDef);
    }
    
    void Shape2D::OnTransformScaleSet(const Transform* const)
    {
        RecreateFixture();
    }
    
}
