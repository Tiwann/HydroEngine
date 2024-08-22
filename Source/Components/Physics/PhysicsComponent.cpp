#include "PhysicsComponent.h"

namespace Hydro
{
    void PhysicsComponent::OnInspectorGUI(const ImGuiIO& IO)
    {
        ImGui::Checkbox("Is Trigger", &m_IsTrigger);
        ImGui::Checkbox("Draw Debug", &m_ShowCollisions);
    }

    bool PhysicsComponent::GetShowCollisions() const
    {
        return m_ShowCollisions;
    }

    void PhysicsComponent::SetShowCollisions(bool Enabled)
    {
        m_ShowCollisions = Enabled;
    }

    PhysicsMaterial PhysicsComponent::GetMaterial() const
    {
        return m_Material;
    }

    void PhysicsComponent::SetMaterial(const PhysicsMaterial& Material)
    {
        m_Material = Material;
    }

    PhysicsConstraintsFlags PhysicsComponent::GetConstraintsFlags() const
    {
        return m_ConstraintsFlags;
    }

    void PhysicsComponent::SetConstraintsFlags(PhysicsConstraintsFlags Constraints)
    {
        m_ConstraintsFlags = Constraints;
    }

    bool PhysicsComponent::IsTrigger() const
    {
        return m_IsTrigger;
    }

    void PhysicsComponent::SetTrigger(bool IsTrigger)
    {
        m_IsTrigger = IsTrigger;
    }

    PhysicsBodyType PhysicsComponent::GetType() const
    {
        return m_Type;
    }

    void PhysicsComponent::SetPhysicsBodyType(PhysicsBodyType Type)
    {
        m_Type = Type;
    }
}
