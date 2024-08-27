﻿#include "PhysicsShape.h"
#include "BoxShape2D.h"
#include "CircleShape2D.h"
#include "BoxShape3D.h"
#include "SphereShape3D.h"

#include <box2d/b2_shape.h>
#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_circle_shape.h>


namespace Hydro
{
    
}

namespace Hydro
{
    BoxShape2D::BoxShape2D(const Vector2& HalfExtents, const Vector2& Center, float Rotation)
        : m_HalfExtents(HalfExtents), m_Center(Center), m_Rotation(Rotation)
    {
        m_Shape = new b2PolygonShape();
        b2PolygonShape* AsPolygonShape = dynamic_cast<b2PolygonShape*>(m_Shape);
        const Vector3 Extents = m_HalfExtents;
        AsPolygonShape->SetAsBox(Extents.x, Extents.y, m_Center, m_Rotation);
    }

    CircleShape2D::CircleShape2D(float Radius, const Vector2& Center)
        : m_Radius(Radius), m_Center(Center)
    {
        m_Shape = new b2CircleShape();
        b2CircleShape* AsCircleShape = dynamic_cast<b2CircleShape*>(m_Shape);
        AsCircleShape->m_p = m_Center;
        AsCircleShape->m_radius = m_Radius;
    }
}


#include <Jolt/Jolt.h>
#include <Jolt/Physics/Collision/Shape/Shape.h>
#include <Jolt/Physics/Collision/Shape/BoxShape.h>
#include <Jolt/Physics/Collision/Shape/SphereShape.h>

namespace Hydro
{
    BoxShape3D::BoxShape3D(Vector3 Center, Vector3 HalfExtents, Vector3 Rotation)
        : m_Center(Center), m_HalfExtents(HalfExtents), m_Rotation(Rotation)
    {
        m_Shape = new JPH::BoxShape(m_HalfExtents);
    }

    SphereShape3D::SphereShape3D(float Radius) : m_Radius(Radius)
    {
        m_Shape = new JPH::SphereShape(m_Radius);
    }
}
