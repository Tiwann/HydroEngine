#include "Core/Physics/PhysicsBody2D.h"
#include "Core/Physics/PhysicsMaterial.h"
#include "Core/Physics/PhysicsWorld2D.h"
#include "Math/Functions.h"

#include <box2d/b2_body.h>
#include <box2d/b2_fixture.h>

namespace Hydro
{
    void PhysicsBody2D::SetUserPointer(void* User)
    {
        b2Body* BodyHandle = GetHandleAs<b2Body>();
        b2BodyUserData& UserData = BodyHandle->GetUserData();
        UserData.pointer = (uintptr_t)User;
    }

    void* PhysicsBody2D::GetUserPointer() const
    {
        const b2Body* BodyHandle = GetHandleAs<b2Body>();
        const b2BodyUserData& UserData = BodyHandle->GetUserData();
        return (void*)UserData.pointer;
    }

    void PhysicsBody2D::CreatePhysicsState(const PhysicsShape2D& Shape, const PhysicsMaterial& Material)
    {
        b2FixtureDef FixtureDefinition = {};
        FixtureDefinition.shape = &Shape.GetShape();
        FixtureDefinition.density = Material.Density;
        FixtureDefinition.friction = Material.Friction;
        FixtureDefinition.restitution = Material.Bounciness;
        //FixtureDefinition.isSensor = m_IsTrigger; // Need to find solution for this

        b2FixtureUserData FixtureUserData{};
        FixtureUserData.pointer = (uintptr_t)this;
        FixtureDefinition.userData = FixtureUserData;
        b2Body* BodyHandle = GetHandleAs<b2Body>();
        m_Fixture = BodyHandle->CreateFixture(&FixtureDefinition);
    }

    void PhysicsBody2D::DestroyPhysicsState()
    {
        b2Body* BodyHandle = GetHandleAs<b2Body>();
        BodyHandle->DestroyFixture(m_Fixture);
        m_Fixture = nullptr;
    }

    void PhysicsBody2D::SetMaterial(const PhysicsMaterial& Material)
    {
        b2Body* BodyHandle = GetHandleAs<b2Body>();
        b2Fixture* Fixture = BodyHandle->GetFixtureList();
        Fixture->SetFriction(Material.Friction);
        Fixture->SetRestitution(Material.Bounciness);
        Fixture->SetDensity(Material.Density);
    }


    void PhysicsBody2D::SetPosition(const Vector3& Position)
    {
        b2Body* BodyHandle = GetHandleAs<b2Body>();
        const float Angle = BodyHandle->GetAngle();
        BodyHandle->SetTransform((Vector2)Position, Angle);
    }

    Vector3 PhysicsBody2D::GetPosition() const
    {
        const b2Body* BodyHandle = GetHandleAs<b2Body>();
        return (Vector3)BodyHandle->GetPosition();
    }

    void PhysicsBody2D::SetRotation(const Vector3& Rotation)
    {
        b2Body* BodyHandle = GetHandleAs<b2Body>();
        const Vector2 Position = BodyHandle->GetPosition();
        BodyHandle->SetTransform(Position, Math::Radians(Rotation.z));
    }

    Vector3 PhysicsBody2D::GetRotation() const
    {
        const b2Body* BodyHandle = GetHandleAs<b2Body>();
        return {0.0f, 0.0, Math::Degrees(BodyHandle->GetAngle())};
    }

    void PhysicsBody2D::SetPositionAndRotation(const Vector3& Position, const Vector3& Rotation)
    {
        b2Body* BodyHandle = GetHandleAs<b2Body>();
        BodyHandle->SetTransform((Vector2)Position, Math::Radians(Rotation.z));
    }

    void PhysicsBody2D::SetGravityScale(float Scale)
    {
        b2Body* BodyHandle = GetHandleAs<b2Body>();
        BodyHandle->SetGravityScale(Scale);
    }

    void PhysicsBody2D::SetLinearVelocity(const Vector3& Velocity)
    {
        b2Body* BodyHandle = GetHandleAs<b2Body>();
        BodyHandle->SetLinearVelocity((Vector2)Velocity);
    }

    void PhysicsBody2D::SetAngularVelocity(const Vector3& AngularVelocity)
    {
        b2Body* BodyHandle = GetHandleAs<b2Body>();
        BodyHandle->SetAngularVelocity(AngularVelocity.z);
    }

    void PhysicsBody2D::SetLinearDamping(float LinearDamping)
    {
        b2Body* BodyHandle = GetHandleAs<b2Body>();
        BodyHandle->SetLinearDamping(LinearDamping);
    }

    void PhysicsBody2D::SetAngularDamping(float AngularDamping)
    {
        b2Body* BodyHandle = GetHandleAs<b2Body>();
        BodyHandle->SetAngularDamping(AngularDamping);
    }

    float PhysicsBody2D::GetGravityScale() const
    {
        const b2Body* BodyHandle = GetHandleAs<b2Body>();
        return BodyHandle->GetGravityScale();
    }

    Vector3 PhysicsBody2D::GetLinearVelocity() const
    {
        const b2Body* BodyHandle = GetHandleAs<b2Body>();
        return Vector2(BodyHandle->GetLinearVelocity());
    }

    Vector3 PhysicsBody2D::GetLinearVelocityPoint(const Vector3& Point) const
    {
        const b2Body* BodyHandle = GetHandleAs<b2Body>();
        return Vector2(BodyHandle->GetLinearVelocityFromLocalPoint(Vector2(Point)));
    }

    Vector3 PhysicsBody2D::GetAngularVelocity() const
    {
        const b2Body* BodyHandle = GetHandleAs<b2Body>();
        return {0.0f, 0.0f, BodyHandle->GetAngularVelocity()};
    }

    float PhysicsBody2D::GetLinearDamping() const
    {
        const b2Body* BodyHandle = GetHandleAs<b2Body>();
        return BodyHandle->GetLinearDamping();
    }

    float PhysicsBody2D::GetAngularDamping() const
    {
        const b2Body* BodyHandle = GetHandleAs<b2Body>();
        return BodyHandle->GetAngularDamping();
    }

    void PhysicsBody2D::AddForce(const Vector3& Force)
    {
    }

    void PhysicsBody2D::AddImpulse(const Vector3& Force)
    {
    }

    void PhysicsBody2D::AddForceAtPosition(const Vector3& Position, const Vector3& Force)
    {
    }

    void PhysicsBody2D::AddImpulseAtPosition(const Vector3& Position, const Vector3& Force)
    {
    }
}
