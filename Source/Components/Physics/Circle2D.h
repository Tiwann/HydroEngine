#pragma once
#include "Shape2D.h"
#include "Math/Vector2.h"

namespace Hydro
{
    class Circle2D : public Shape2D
    {
    public:
        Circle2D(GameObject* Owner);

        void OnInspectorGUI(const ImGuiIO& IO) override;

        Vector2 GetCenter() const;
        void SetCenter(const Vector2& Center);

        float GetRadius() const;
        void SetRadius(float radius);
        void OnPhysicsUpdate(float Delta) override;
    protected:
        Vector2 m_Center = Vector2::Zero;
        float m_Radius = 1.0f;
        b2Shape* CreateShape() override;
        void RenderCollisions(const Ref<RendererBackend>& Renderer) const override;
    };
}
