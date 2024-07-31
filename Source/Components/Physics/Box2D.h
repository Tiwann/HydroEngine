#pragma once
#include "Shape2D.h"
#include "Math/Vector2.h"

class b2Shape;

namespace Hydro
{
    class Box2D : public Shape2D
    {
    public:
        Box2D(GameObject* Owner);
        void OnInspectorGUI(const ImGuiIO& IO) override;
        
        Vector2 GetCenter() const;
        void SetCenter(const Vector2& Center);

        Vector2 GetHalfExtents() const;
        void SetHalfExtents(const Vector2& HalfExtents);

    protected:
        Vector2 m_Center = Vector2::Zero;
        Vector2 m_HalfExtents{0.5f, 0.5f};
        b2Shape* CreateShape() override;

        void OnPhysicsUpdate(float Delta) override;
        void RenderCollisions(const Ref<RendererBackend>& Renderer) const override;
    };
}

