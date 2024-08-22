#pragma once
#include "Math/Vector3.h"
#include <cstdint>

namespace Hydro
{
    struct PhysicsMaterial;
    
    template<typename ShapeBase, typename WorldBase>
    class PhysicsBody
    {
    public:
        explicit PhysicsBody(const uintptr_t Handle, WorldBase& World) : m_Handle(Handle), m_World(&World){ }
        virtual ~PhysicsBody() = default;
        PhysicsBody(const PhysicsBody&) = delete;
        PhysicsBody(PhysicsBody&&) noexcept = delete;
        PhysicsBody& operator=(const PhysicsBody&) = delete;
        PhysicsBody& operator=(PhysicsBody&&) noexcept = delete;


        virtual void CreatePhysicsState(const ShapeBase& Shape, const PhysicsMaterial& Material) = 0;
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

        virtual void SetMaterial(const PhysicsMaterial& Material) = 0;

        template<typename T>
        T* GetHandleAs() { return reinterpret_cast<T*>(m_Handle); }

        template<typename T>
        const T* GetHandleAs() const { return reinterpret_cast<T*>(m_Handle); }
        
        WorldBase* GetWorld() { return m_World; }
        const WorldBase* GetWorld() const { return m_World; }
    private:
        uintptr_t m_Handle = 0;
        WorldBase* m_World = nullptr;
    };
}
