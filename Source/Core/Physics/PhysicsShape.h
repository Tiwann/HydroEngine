#pragma once
#include "PhysicsShape.h"
#include "Math/Vector2.h"
#include "Math/Matrix4.h"
#include "Core/Memory.h"

#include <box2d/b2_shape.h>
#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_circle_shape.h>

#include <Jolt/Jolt.h>
#include <Jolt/Physics/Collision/Shape/Shape.h>
#include <Jolt/Physics/Collision/Shape/BoxShape.h>
#include <Jolt/Physics/Collision/Shape/SphereShape.h>


namespace Hydro
{
    
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// INTERFACE
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename Handle>
    class PhysicsShape
    {
    public:
        using HandleType = Handle;
        PhysicsShape() = default;
        PhysicsShape(const PhysicsShape& Other) : m_Shape(Other.m_Shape){}
        PhysicsShape(PhysicsShape&& Other) noexcept : m_Shape(Other.m_Shape){ Other.m_Shape = nullptr; }
        
        PhysicsShape& operator=(const PhysicsShape& Other)
        {
            if(this == &Other)
                return *this;
            m_Shape = Other.m_Shape;
            return *this;
        }
        PhysicsShape& operator=(PhysicsShape&& Other) noexcept
        {
            if(this == &Other)
                return *this;
            m_Shape = Other.m_Shape;
            Other.m_Shape = nullptr;
            return *this;
        }
        
        virtual ~PhysicsShape()
        {
            delete m_Shape;
            m_Shape = nullptr;
        }
        
        Handle& GetShape() { return *m_Shape; }
        const Handle& GetShape() const { return *m_Shape; }
    protected:
        Handle* m_Shape = nullptr;
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Shape2D
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    class PhysicsShape2D : public PhysicsShape<b2Shape>
    {
    public:
        PhysicsShape2D() : PhysicsShape() {}
        using HandleType = PhysicsShape::HandleType;
        
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Shape3D
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    class PhysicsShape3D : public PhysicsShape<JPH::Shape>
    {
    public:
        using HandleType = PhysicsShape::HandleType;
        PhysicsShape3D() : PhysicsShape() { }
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Box2D
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    class BoxShape2D : public PhysicsShape2D
    {
    public:
        explicit BoxShape2D(const Vector2& HalfExtents, const Vector2& Center, float Rotation)
        : m_HalfExtents(HalfExtents), m_Center(Center), m_Rotation(Rotation)
        {
            m_Shape = new b2PolygonShape();
            b2PolygonShape* AsPolygonShape = dynamic_cast<b2PolygonShape*>(m_Shape);
            const Vector3 Extents = m_HalfExtents;
            AsPolygonShape->SetAsBox(Extents.x, Extents.y, m_Center, m_Rotation);
        }
    private:
        Vector2 m_HalfExtents;
        Vector2 m_Center;
        float m_Rotation = 0.0f;
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Circle2D
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    class CircleShape2D : public PhysicsShape2D
    {
    public:
        explicit CircleShape2D(float Radius, const Vector2& Center)
        : m_Radius(Radius), m_Center(Center)
        {
            m_Shape = new b2CircleShape();
            b2CircleShape* AsCircleShape = dynamic_cast<b2CircleShape*>(m_Shape);
            AsCircleShape->m_p = m_Center;
            AsCircleShape->m_radius = m_Radius;
        }
    private:
        float m_Radius;
        Vector2 m_Center;
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Box3D
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    class BoxShape3D : public PhysicsShape3D
    {
    public:
        explicit BoxShape3D(Vector3 Center, Vector3 HalfExtents, Vector3 Rotation)
        : m_Center(Center), m_HalfExtents(HalfExtents), m_Rotation(Rotation)
        {
            m_Shape = new JPH::BoxShape(m_HalfExtents);
        }
    private:
        Vector3 m_Center;
        Vector3 m_HalfExtents;
        Vector3 m_Rotation;
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Sphere3D
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    class SphereShape3D : public PhysicsShape3D
    {
    public:
        explicit SphereShape3D(float Radius) : m_Radius(Radius)
        {
            m_Shape = new JPH::SphereShape(m_Radius);
        }
    private:
        float m_Radius;
    };
    
    
}
