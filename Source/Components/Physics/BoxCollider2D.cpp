#include "HydroPCH.h"
#include "BoxCollider2D.h"
#include "Core/Scene.h"
#include "Components/Transform.h"

#include <box2d/b2_polygon_shape.h>

namespace Hydro
{
    BoxCollider2D::BoxCollider2D() : Collider2D("Box Collider 2D")
    {
        
    }

    BoxCollider2D::BoxCollider2D(Vector2 Center, Vector2 HalfExtents)
    : Collider2D("Box Collider 2D"), Center(Center), HalfExtents(HalfExtents)
    {
        
    }

    void BoxCollider2D::OnInit()
    {
        Collider2D::OnInit();
       
    }

    void BoxCollider2D::OnUpdate(float Delta)
    {
        Collider2D::OnUpdate(Delta);
        
    }

    void BoxCollider2D::OnCollisionEnterImplementation(const Collision2D& Collision)
    {
    }

    void BoxCollider2D::OnCollisionStayImplementation(const Collision2D& Collision)
    {
    }

    void BoxCollider2D::OnCollisionExitImplementation(const Collision2D& Collision)
    {
    }
    
    b2Shape* BoxCollider2D::CreateShape()
    {
        b2PolygonShape* Shape = new b2PolygonShape();
        const float ZRotation = GetTransform()->GetRotation().z;
        Shape->SetAsBox(HalfExtents.x, HalfExtents.y, Center, ZRotation);
        return Shape;
    }
}
