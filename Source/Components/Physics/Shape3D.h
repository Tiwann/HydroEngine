#pragma once
#include "PhysicsComponent.h"

namespace Hydro
{
    struct Collision3D;
    
    class Shape3D : public PhysicsComponent, public ICollisionResponse<Collision3D>
    {
    public:
        Shape3D(GameObject* Owner, const std::string& Name) : PhysicsComponent(Owner, Name)
        {
            
        }

        void OnInit() override;

        void SetGravityEnabled(bool Enabled) const override;
        void SetGravityScale(float Scale) override;
        void SetLinearVelocity(const Vector3& Velocity) const override;
        void SetAngularVelocity(float AngularVelocity) const override;
        void SetLinearDamping(float LinearDamping) const override;
        void SetAngularDamping(float AngularDamping) const override;
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
    };
}
