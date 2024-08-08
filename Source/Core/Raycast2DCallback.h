#pragma once
#include "Core/RaycastHit.h"
#include <box2d/b2_world_callbacks.h>


namespace Hydro
{
    class Raycast2DCallback : public b2RayCastCallback
    {
    public:
        RaycastHit2D HitInfo;
        float ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float fraction) override;
    };
}
