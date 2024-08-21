#pragma once
#include "PhysicsComponent.h"
#include "Math/Vector2.h"
#include "Core/Physics/PhysicsBody2D.h"

class b2Fixture;
class b2Body;
class b2Shape;

namespace Hydro
{
    class Vector3;
    struct Collision2D;
    class Transform;
    
    class Shape2D : public PhysicsComponent, public ICollisionResponse<Collision2D>
    {
    protected:
        friend class GameObject;
        Shape2D(GameObject* Owner, const std::string& Name);
        virtual b2Shape* CreateShape() = 0;
        
        void OnInit() override;
        void OnStart() override;
        void OnDestroy() override;
        void OnPhysicsUpdate(float Delta) override;

        

    public:
        float GetGravityScale() const override;
        void SetGravityScale(float Scale) override;
        void SetGravityEnabled(bool Enabled) const override;
        void SetLinearVelocity(const Vector3& Velocity) const override;
        void SetAngularVelocity(float AngularVelocity) const override;
        void SetLinearDamping(float LinearDamping) const override;
        void SetAngularDamping(float AngularDamping) const override;
        
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
        void SetType(ColliderType Type) override;

        void RecreatePhysicsState() override;
    protected:
        friend class Shape2DContactListener;
        b2Shape* m_Shape{nullptr};
        b2Body* m_Body{nullptr};
        b2Fixture* m_Fixture{nullptr};
        Shape2DContactListener* m_ContactListener{nullptr};
        bool IsColliding = false;

        PhysicsBody* m_BODY;
        void RenderCollisions(const Ref<RendererBackend>& Renderer) const override = 0;
    };
}
