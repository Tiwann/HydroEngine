#include "HydroPCH.h"
#include "Raycast2DCallback.h"

#include <box2d/b2_fixture.h>

namespace Hydro
{
    float Raycast2DCallback::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal,
        float fraction)
    {
        const RigidBody2D* Collider = (RigidBody2D*)fixture->GetUserData().pointer;
        if(Collider->IsTrigger())
        {
            return 1;
        }

        HitInfo.Point = point;
        HitInfo.Normal = normal;
        return fraction;
    }
}
