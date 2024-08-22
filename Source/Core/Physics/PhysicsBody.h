#pragma once
#include "Math/Vector3.h"
#include "Core/Physics/PhysicsMaterial.h"
#include <cstdint>

#include "PhysicsShape.h"

namespace Hydro
{
    template<typename ShapeBase, typename WorldBase, typename BodyHandle>
    class PhysicsBody
    {
    public:
        explicit PhysicsBody(BodyHandle* Handle, WorldBase& World) : m_Handle(Handle), m_World(&World){ }
        virtual ~PhysicsBody() = default;
        PhysicsBody(const PhysicsBody&) = delete;
        PhysicsBody(PhysicsBody&&) noexcept = delete;
        PhysicsBody& operator=(const PhysicsBody&) = delete;
        PhysicsBody& operator=(PhysicsBody&&) noexcept = delete;


        virtual void CreatePhysicsState(ShapeBase* Shape, const PhysicsMaterial& Material)
        {
            m_Shape = dynamic_cast<ShapeBase*>(Shape);
            m_Material = Material;
        }
        
        virtual void DestroyPhysicsState() = 0;
        
        virtual void SetUserPointer(void* User) = 0;
        virtual void* GetUserPointer() const = 0;

        virtual void SetPosition(const Vector3& Position) = 0;
        virtual Vector3 GetPosition() const = 0;
        virtual void SetRotation(const Vector3& Rotation) = 0;
        virtual Vector3 GetRotation() const = 0;
        virtual void SetPositionAndRotation(const Vector3& Position, const Vector3& Rotation) = 0;
        
        virtual void SetGravityScale(float Scale) = 0;
        virtual void SetLinearVelocity(const Vector3& Velocity) = 0;
        virtual void SetAngularVelocity(const Vector3& AngularVelocity) = 0;
        virtual void SetLinearDamping(float LinearDamping) = 0;
        virtual void SetAngularDamping(float AngularDamping) = 0;

        virtual float GetGravityScale() const = 0;
        virtual Vector3 GetLinearVelocity() const = 0;
        virtual Vector3 GetAngularVelocity() const = 0;
        virtual float GetLinearDamping() const = 0;
        virtual float GetAngularDamping() const = 0;
        virtual Vector3 GetLinearVelocityPoint(const Vector3& Point) const = 0;

        virtual void AddForce(const Vector3& Force) = 0;
        virtual void AddImpulse(const Vector3& Force) = 0;
        virtual void AddForceAtPosition(const Vector3& Position, const Vector3& Force) = 0;
        virtual void AddImpulseAtPosition(const Vector3& Position, const Vector3& Force) = 0;

        virtual void SetMaterial(const PhysicsMaterial& Material)
        {
            m_Material = Material;
        }

        BodyHandle* GetHandle() { return m_Handle; }
        const BodyHandle* GetHandle() const { return m_Handle; }

        WorldBase* GetWorld() { return m_World; }
        const WorldBase* GetWorld() const { return m_World; }

        ShapeBase* GetShape() { return m_Shape; }
        const ShapeBase* GetShape() const { return m_Shape; }
    private:
        BodyHandle* m_Handle = nullptr;
        WorldBase* m_World = nullptr;
        ShapeBase* m_Shape = nullptr;
        PhysicsMaterial m_Material;
    };
}
