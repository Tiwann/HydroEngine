﻿#include "ScriptComponent.h"
#include "Components/Physics/RigidBody2D.h"
#include "Components/Physics/RigidBody3D.h"
#include "Core/Entity.h"
#include "Core/Containers/DynamicArray.h"

namespace Hydro
{
    void ScriptComponent::OnInit()
    {
        Component::OnInit();

        for(const auto& RB2Ds = m_Entity->GetAllComponents<RigidBody2D>(); auto& Rigidbody : RB2Ds)
        {
            Rigidbody->OnContactBeginEvent.BindMember(this, &ScriptComponent::OnContactBegin2D);
            Rigidbody->OnContactStayEvent.BindMember(this, &ScriptComponent::OnContactStay2D);
            Rigidbody->OnContactEndEvent.BindMember(this, &ScriptComponent::OnContactEnd2D);
        }

        for(const auto& RB3Ds = m_Entity->GetAllComponents<RigidBody3D>(); auto& Rigidbody : RB3Ds)
        {
            Rigidbody->OnContactBeginEvent.BindMember(this, &ScriptComponent::OnContactBegin3D);
            Rigidbody->OnContactStayEvent.BindMember(this, &ScriptComponent::OnContactStay3D);
            Rigidbody->OnContactEndEvent.BindMember(this, &ScriptComponent::OnContactEnd3D);
        }
    }

    void ScriptComponent::OnDestroy()
    {
        Component::OnDestroy();
    }
}