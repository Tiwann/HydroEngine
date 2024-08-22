#pragma once
#include "PhysicsComponent.h"

namespace Hydro
{
    struct Collision3D;
    struct PhysicsMaterial;
    
    class Collider3D : public PhysicsComponent, public ICollisionResponse<Collision3D>
    {
    public:
        friend class GameObject;
        Collider3D(GameObject* Owner, const std::string& Name) : PhysicsComponent(Owner, Name)
        {
            
        }

        void OnInit() override;
        void OnStart() override;
        void OnPhysicsUpdate(float Delta) override;
        

        void SetGravityEnabled(bool Enabled) override;
        void SetGravityScale(float Scale) override;
        void SetLinearVelocity(const Vector3& Velocity) override;
        void SetAngularVelocity(const Vector3& AngularVelocity) override;
        void SetLinearDamping(float LinearDamping) override;
        void SetAngularDamping(float AngularDamping) override;
        float GetGravityScale() const override;
        Vector3 GetLinearVelocity() const override;
        float GetAngularVelocity() const override;
        float GetLinearDamping() const override;
        float GetAngularDamping() const override;
        Vector3 GetLinearVelocityPoint(const Vector3& Point) const override;
        void AddForce(const Vector3& Force) override;
        void AddImpulse(const Vector3& Force) override;
        void AddForceAtPosition(const Vector3& Position, const Vector3& Force) override;
        void AddImpulseAtPosition(const Vector3& Position, const Vector3& Force) override;
        
        void RecreatePhysicsState() override;
        void SetMaterial(const PhysicsMaterial& Material) override;
        void SetConstraintsFlags(PhysicsConstraintsFlags Constraints) override;
        void SetTrigger(bool IsTrigger) override;
        void SetPhysicsBodyType(PhysicsBodyType Type) override;

    protected:
        
    };
}
