#include "Core/Physics/PhysicsBody3D.h"
#include "PhysicsWorld3D.h"
#include "PhysicsShape3D.h"
#include "Math/Functions.h"

#include <Jolt/Jolt.h>
#include <Jolt/Physics/Body/Body.h>

#include "PhysicsMaterial.h"


namespace Hydro
{
    void PhysicsBody3D::SetUserPointer(void* User)
    {
        Body* BodyHandle = GetHandle();
        BodyHandle->SetUserData((JPH::uint64)User);
    }

    void* PhysicsBody3D::GetUserPointer() const
    {
        const Body* BodyHandle = GetHandle();
        return (void*)BodyHandle->GetUserData();
    }

    void PhysicsBody3D::CreatePhysicsState(PhysicsShape3D* Shape, const PhysicsMaterial& Material)
    {
        const PhysicsWorld3D* World = GetWorld();
        const JPH::PhysicsSystem& System = World->GetSystem();
        const JPH::BodyInterface& BodyInterface = System.GetBodyInterface();
        const Body* BodyHandle = GetHandle();
        const JPH::Shape& ShapeHandle = Shape->GetHandle();
        BodyInterface.SetShape(BodyHandle->GetID(), &ShapeHandle, true, JPH::EActivation::Activate);
    }

    void PhysicsBody3D::DestroyPhysicsState()
    {
        
    }

    void PhysicsBody3D::SetPosition(const Vector3& Position)
    {
        PhysicsWorld3D* World = GetWorld();
        JPH::PhysicsSystem& System = World->GetSystem();
        JPH::BodyInterface& BodyInterface = System.GetBodyInterface();
        const Body* BodyHandle = GetHandle();
        BodyInterface.SetPosition(BodyHandle->GetID(), Position, JPH::EActivation::Activate);
    }

    Vector3 PhysicsBody3D::GetPosition() const
    {
        const PhysicsWorld3D* World = GetWorld();
        const JPH::PhysicsSystem& System = World->GetSystem();
        const JPH::BodyInterface& BodyInterface = System.GetBodyInterface();
        const Body* BodyHandle = GetHandle();
        return BodyInterface.GetPosition(BodyHandle->GetID());
    }

    void PhysicsBody3D::SetRotation(const Vector3& Rotation)
    {
        PhysicsWorld3D* World = GetWorld();
        JPH::PhysicsSystem& System = World->GetSystem();
        JPH::BodyInterface& BodyInterface = System.GetBodyInterface();
        const Body* BodyHandle = GetHandle();
        const JPH::Quat NewRotation = JPH::Quat::sEulerAngles(Rotation.Apply(Math::Radians));
        BodyInterface.SetRotation(BodyHandle->GetID(), NewRotation, JPH::EActivation::Activate);
    }

    Vector3 PhysicsBody3D::GetRotation() const
    {
        const PhysicsWorld3D* World = GetWorld();
        const JPH::PhysicsSystem& System = World->GetSystem();
        const JPH::BodyInterface& BodyInterface = System.GetBodyInterface();
        const Body* BodyHandle = GetHandle();
        return Vector3(BodyInterface.GetRotation(BodyHandle->GetID()).GetEulerAngles()).Apply(Math::Degrees);
    }

    void PhysicsBody3D::SetPositionAndRotation(const Vector3& Position, const Vector3& Rotation)
    {
        PhysicsWorld3D* World = GetWorld();
        JPH::PhysicsSystem& System = World->GetSystem();
        JPH::BodyInterface& BodyInterface = System.GetBodyInterface();
        const Body* BodyHandle = GetHandle();
        const JPH::Quat NewRotation = JPH::Quat::sEulerAngles(Rotation.Apply(Math::Radians));
        BodyInterface.SetPositionAndRotation(BodyHandle->GetID(), Position, NewRotation, JPH::EActivation::Activate);
    }

    void PhysicsBody3D::SetGravityScale(f32 Scale)
    {
        Body* BodyHandle = GetHandle();
        JPH::MotionProperties* MotionProperties = BodyHandle->GetMotionProperties();
        MotionProperties->SetGravityFactor(Scale);
    }

    void PhysicsBody3D::SetLinearVelocity(const Vector3& Velocity)
    {
        Body* BodyHandle = GetHandle();
        JPH::MotionProperties* MotionProperties = BodyHandle->GetMotionProperties();
        MotionProperties->SetLinearVelocity(Velocity);
    }

    void PhysicsBody3D::SetAngularVelocity(const Vector3& AngularVelocity)
    {
        Body* BodyHandle = GetHandle();
        JPH::MotionProperties* MotionProperties = BodyHandle->GetMotionProperties();
        MotionProperties->SetAngularVelocity(AngularVelocity);
    }

    void PhysicsBody3D::SetLinearDamping(f32 LinearDamping)
    {
        Body* BodyHandle = GetHandle();
        JPH::MotionProperties* MotionProperties = BodyHandle->GetMotionProperties();
        MotionProperties->SetLinearDamping(LinearDamping);
    }

    void PhysicsBody3D::SetAngularDamping(f32 AngularDamping)
    {
        Body* BodyHandle = GetHandle();
        JPH::MotionProperties* MotionProperties = BodyHandle->GetMotionProperties();
        MotionProperties->SetAngularDamping(AngularDamping);
    }

    f32 PhysicsBody3D::GetGravityScale() const
    {
        const Body* BodyHandle = GetHandle();
        const JPH::MotionProperties* MotionProperties = BodyHandle->GetMotionProperties();
        return MotionProperties->GetGravityFactor();
    }

    Vector3 PhysicsBody3D::GetLinearVelocity() const
    {
        const Body* BodyHandle = GetHandle();
        const JPH::MotionProperties* MotionProperties = BodyHandle->GetMotionProperties();
        return MotionProperties->GetLinearVelocity();
    }


    Vector3 PhysicsBody3D::GetLinearVelocityPoint(const Vector3& Point) const
    {
        const Body* BodyHandle = GetHandle();
        const JPH::MotionProperties* MotionProperties = BodyHandle->GetMotionProperties();
        return MotionProperties->GetPointVelocityCOM(Point);
    }


    Vector3 PhysicsBody3D::GetAngularVelocity() const
    {
        const Body* BodyHandle = GetHandle();
        const JPH::MotionProperties* MotionProperties = BodyHandle->GetMotionProperties();
        return MotionProperties->GetAngularVelocity();
    }

    f32 PhysicsBody3D::GetLinearDamping() const
    {
        const Body* BodyHandle = GetHandle();
        const JPH::MotionProperties* MotionProperties = BodyHandle->GetMotionProperties();
        return MotionProperties->GetLinearDamping();
    }

    f32 PhysicsBody3D::GetAngularDamping() const
    {
        const Body* BodyHandle = GetHandle();
        const JPH::MotionProperties* MotionProperties = BodyHandle->GetMotionProperties();
        return MotionProperties->GetAngularDamping();
    }

    void PhysicsBody3D::AddForce(const Vector3& Force)
    {
        Body* BodyHandle = GetHandle();
        BodyHandle->AddForce(Force);
    }

    void PhysicsBody3D::AddImpulse(const Vector3& Force)
    {
        Body* BodyHandle = GetHandle();
        BodyHandle->AddImpulse(Force);
    }

    void PhysicsBody3D::AddForceAtPosition(const Vector3& Position, const Vector3& Force)
    {
        Body* BodyHandle = GetHandle();
        BodyHandle->AddForce(Force, Position);
    }

    void PhysicsBody3D::AddImpulseAtPosition(const Vector3& Position, const Vector3& Force)
    {
        Body* BodyHandle = GetHandle();
        BodyHandle->AddImpulse(Force, Position);
    }

    const PhysicsConstraintsFlags& PhysicsBody3D::GetConstraints() const
    {
        return m_Constraints;
    }

    void PhysicsBody3D::SetConstraints(const PhysicsConstraintsFlags& Constraints)
    {
        m_Constraints = Constraints;
        // TODO: Jolt Physics constrains handling (JPH::EAllowedDOFs)
    }

    const PhysicsMaterial& PhysicsBody3D::GetMaterial() const
    {
        return m_Material;
    }

    void PhysicsBody3D::SetMaterial(const PhysicsMaterial& Material)
    {
        m_Material = Material;
        Body* BodyHandle = GetHandle();
        BodyHandle->SetFriction(m_Material.Friction);
        BodyHandle->SetRestitution(m_Material.Bounciness);
    }

    PhysicsBodyType PhysicsBody3D::GetType() const
    {
        return m_Type;
    }

    void PhysicsBody3D::SetType(PhysicsBodyType Type)
    {
        m_Type = Type;
        PhysicsWorld3D* World = GetWorld();
        JPH::PhysicsSystem& System = World->GetSystem();
        JPH::BodyInterface& Interface = System.GetBodyInterface();
        const Body* BodyHandle = GetHandle();
        Interface.SetMotionType(BodyHandle->GetID(), (JPH::EMotionType)m_Type, JPH::EActivation::Activate);
    }

    bool PhysicsBody3D::IsSensor()
    {
        return m_IsSensor;
    }

    void PhysicsBody3D::SetIsSensor(bool Sensor)
    {
        m_IsSensor = Sensor;
        Body* BodyHandle = GetHandle();
        BodyHandle->SetIsSensor(m_IsSensor);
    }
}
