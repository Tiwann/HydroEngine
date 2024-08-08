#include "HydroPCH.h"
#include "Raycast2DCallback.h"

namespace Hydro
{
    float Raycast2DCallback::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal,
        float fraction)
    {
        const Shape2D* Collider = (Shape2D*)fixture->GetUserData().pointer;
        if(Collider->IsTrigger())
        {
            return 1;
        }

        HitInfo.Point = point;
        HitInfo.Normal = normal;
        return fraction;
    }
}
