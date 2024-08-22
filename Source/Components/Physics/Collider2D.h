#pragma once
#include "PhysicsComponent.h"


namespace Hydro
{
    class Vector3;
    struct Collision2D;
    class Transform;
    class PhysicsBody2D;
    struct PhysicsMaterial;
    class PhysicsShape2D;
    
    class Collider2D : public PhysicsComponent, public ICollisionResponse<Collision2D>
    {
    protected:
        friend class GameObject;
        Collider2D(GameObject* Owner, const std::string& Name);
        
        virtual PhysicsShape2D* CreateShape() = 0;
        
        void OnInit() override;
        void OnStart() override;
        void OnDestroy() override;
        void OnPhysicsUpdate(float Delta) override;
    
    public:
        float GetGravityScale() const override;
        void SetGravityScale(float Scale) override;
        void SetGravityEnabled(bool Enabled) override;
        void SetLinearVelocity(const Vector3& Velocity) override;
        void SetAngularVelocity(const Vector3& AngularVelocity) override;
        void SetLinearDamping(float LinearDamping) override;
        void SetAngularDamping(float AngularDamping) override;
        
        Vector3 GetLinearVelocity() const override;
        float GetAngularVelocity() const override;
        float GetLinearDamping() const override;
        float GetAngularDamping() const override;
        Vector3 GetLinearVelocityPoint(const Vector3& Point) const override;
        
        void AddForce(const Vector3& Force) override;
        void AddImpulse(const Vector3& Force) override;
        void AddForceAtPosition(const Vector3& Position, const Vector3& Force) override;
        void AddImpulseAtPosition(const Vector3& Position, const Vector3& Force) override;
        void SetPosition(const Vector3& Position) const;
        void SetRotation(float Rotation) const;

        void SetMaterial(const PhysicsMaterial& Material) override;
        void SetConstraintsFlags(PhysicsConstraintsFlags Constraints) override;
        void SetTrigger(bool IsTrigger) override;
        void SetPhysicsBodyType(PhysicsBodyType Type) override;

        void RecreatePhysicsState() override;
    protected:
        friend class Shape2DContactListener;
        Shape2DContactListener* m_ContactListener{nullptr};
        bool IsColliding = false;
        
        PhysicsBody2D* m_PhysicsBody;
        PhysicsShape2D* m_PhysicsShape;
        void RenderCollisions(const Ref<RendererBackend>& Renderer) const override = 0;
    };
}
