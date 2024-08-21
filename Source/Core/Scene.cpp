#include "HydroPCH.h"
#include "Scene.h"

#include "Application.h"
#include "GameObject.h"
#include "Core/Physics/Physics2D.h"
#include "Time.h"
#include "box2d/box2d.h"
#include "Components/Transform.h"


#include <Jolt/RegisterTypes.h>
#include <Jolt/Core/Memory.h>
#include <Jolt/Physics/PhysicsSystem.h>

#include "Core/Physics/Physics3D.h"

namespace Hydro
{
    void Scene::OnInit()
    {
        m_PhysicsWorld2D.OnInit();
        m_PhysicsWorld3D.OnInit();
        
        
        m_RendererBackend = Application::GetCurrentApplication().GetRendererBackend();
        
        for(const Ref<GameObject>& Object : m_GameObjects)
        {
            Object->OnInit();
        }
    }

    void Scene::OnUpdate(float Delta)
    {
        for(const Ref<GameObject>& Object : m_GameObjects)
        {
            Object->OnUpdate(Delta);
        }

        m_PhysicsWorld2D.Step(Physics2D::TimeStep);
        m_PhysicsWorld3D.Step(Physics3D::TimeStep);

        for(const Ref<GameObject>& Object : m_GameObjects)
        {
            Object->OnPhysicsUpdate(Delta);
        }
    }

    void Scene::OnRender(const Ref<RendererBackend>& Renderer) const
    {
        for(const Ref<GameObject>& Object : m_GameObjects)
        {
            Object->OnRender(Renderer);
        }
    }

    void Scene::OnDestroy()
    {
        for(Ref<GameObject>& Object : m_GameObjects)
        {
            Object->OnDestroy();
        }
        
        m_PhysicsWorld2D.OnDestroy();
        m_PhysicsWorld3D.OnDestroy();
    }
    
    bool Scene::DestroyObject(Ref<GameObject>& Object)
    {
        Object->OnDestroy();
        const auto Index = std::ranges::find(m_GameObjects, Object);
        m_GameObjects.erase(Index);
        Object.reset();
        return true;
    }

    void Scene::SetName(const std::string& Name)
    {
        m_Name = Name;
    }
}
