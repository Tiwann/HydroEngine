#pragma once
#include "Collider2D.h"
#include <box2d/box2d.h>

#include "Math/Vector2.h"

namespace Hydro
{
    class BoxCollider2D : public Collider2D
    {
    public:
        BoxCollider2D();
        BoxCollider2D(Vector2 Center, Vector2 HalfExtents);

        Vector2 Center;
        Vector2 HalfExtents{1.0f, 1.0f};
    protected:
        void OnInit() override;
        void OnUpdate(float Delta) override;
        
        void OnCollisionEnterImplementation(const Collision2D& Collision) override;
        void OnCollisionStayImplementation(const Collision2D& Collision) override;
        void OnCollisionExitImplementation(const Collision2D& Collision) override;
        
        b2Shape* CreateShape() override;
    };
}

