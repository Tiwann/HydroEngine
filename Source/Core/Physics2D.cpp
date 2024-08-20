#include "HydroPCH.h"
#include "Physics2D.h"

#include "Application.h"
#include "Buffer.h"
#include "RaycastHit.h"
#include "Scene.h"

#include <box2d/b2_body.h>
#include <box2d/b2_collision.h>
#include <box2d/b2_world.h>
#include <box2d/b2_circle_shape.h>
#include <box2d/b2_fixture.h>

#include "Ray.h"
#include "Raycast2DCallback.h"

namespace Hydro
{
    Vector2 Physics2D::Gravity = { 0.0f, -9.81f };
    float Physics2D::TimeStep = 1.0f / 60.0f;
    
    bool Physics2D::CheckCircle(const Vector3& Center, float Radius)
    {
        const Ref<Scene>& CurrentScene = Application::GetCurrentApplication().GetScene();
        const b2World* CurrentWorld = CurrentScene->m_Physics2DWorld;
        const BufferView BodiesView(CurrentWorld->GetBodyList(), CurrentWorld->GetBodyCount());

        b2CircleShape CircleShape;
        CircleShape.m_radius = Radius;
        CircleShape.m_p = (Vector2)Center;
        CircleShape.m_type = b2Shape::e_circle;
        
        for(const auto& Body : BodiesView)
        {
            for(const b2Fixture* Fixture = Body.GetFixtureList(); Fixture; Fixture = Fixture->GetNext())
            {
                const b2Shape* ShapeA = Fixture->GetShape();
                const b2Transform TransformA = Body.GetTransform();
                const b2Shape* ShapeB = &CircleShape;
                const b2Transform TransformB = {Vector2::Zero, b2Rot(0.0f)};
                if(b2TestOverlap(ShapeA, 0, ShapeB, 0, TransformA, TransformB))
                    return true;
            }
        }
        return false;
    }

    RaycastHit2D Physics2D::Raycast(const Ray& Ray, float Distance)
    {
        const Ref<Scene>& CurrentScene = Application::GetCurrentApplication().GetScene();
        const b2World* CurrentWorld = CurrentScene->m_Physics2DWorld;

        Raycast2DCallback Callback;
        CurrentWorld->RayCast(&Callback, (Vector2)Ray.Position, (Vector2)Ray.Position + Ray.Direction * Distance);
        return Callback.HitInfo;
    }
}
