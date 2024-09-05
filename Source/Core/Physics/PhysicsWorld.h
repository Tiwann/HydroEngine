#pragma once
#include "PhysicsBody3D.h"
#include "Core/Physics/PhysicsBodyDefinition.h"
#include "Core/Containers/DynamicArray.h"

namespace Hydro
{
    struct PhysicsMaterial;
    
    template<typename BodyType, typename ShapeType>
    class PhysicsWorld
    {
    public:
        virtual ~PhysicsWorld() = default;
        virtual void OnInit() = 0;
        virtual void Step(f32 TimeStep) = 0;
        virtual void OnDestroy() = 0;
        virtual void OnContactBegin(BodyType* BodyA, BodyType* BodyB) = 0;
        virtual void OnContactEnd(BodyType* BodyA, BodyType* BodyB) = 0;
        
        virtual BodyType* CreateBody(const PhysicsBodyDefinition& Definition, const PhysicsMaterial& Material) = 0;
        virtual void DestroyBody(BodyType* Body) = 0;
        virtual void SetMaterial(BodyType* Body, const PhysicsMaterial& Material) = 0;

        // User can't modify this array neither modify the bodies contained in it
        const Array<const BodyType*>& GetBodies() const { return m_Bodies; }
    protected:
        Array<const BodyType*> m_Bodies;
    };
    
}
