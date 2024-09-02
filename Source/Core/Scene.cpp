#include "Scene.h"
#include "Application.h"
#include "Entity.h"
#include "Core/Physics/Physics2D.h"
#include "Core/Physics/Physics3D.h"


namespace Hydro
{
    void Scene::OnInit()
    {
        m_PhysicsWorld2D.OnInit();
        //m_PhysicsWorld3D.OnInit();
        
        
        m_RendererBackend = g_Application->GetRendererBackend();
        
        for(const Ref<Entity>& Entity : m_Entities)
        {
            Entity->OnInit();
        }
    }

    void Scene::OnUpdate(f32 Delta)
    {
        for(const Ref<Entity>& Entity : m_Entities)
        {
            Entity->OnUpdate(Delta);
        }

        m_PhysicsWorld2D.Step(Physics2D::TimeStep);
        //m_PhysicsWorld3D.Step(Physics3D::TimeStep);

        for(const Ref<Entity>& Entity : m_Entities)
        {
            Entity->OnPhysicsUpdate(Delta);
        }
    }

    void Scene::OnRender(const Ref<RendererBackend>& Renderer) const
    {
        for(const Ref<Entity>& Entity : m_Entities)
        {
            Entity->OnRender(Renderer);
        }
    }

    void Scene::OnDestroy()
    {
        for(Ref<Entity>& Entity : m_Entities)
        {
            Entity->OnDestroy();
        }
        
        m_PhysicsWorld2D.OnDestroy();
        //m_PhysicsWorld3D.OnDestroy();
    }
    
    bool Scene::DestroyEntity(Ref<Entity>& Entity)
    {
        Entity->OnDestroy();
        m_Entities.Remove(Entity);
        Entity.reset();
        return true;
    }

    void Scene::SetName(const std::string& Name)
    {
        m_Name = Name;
    }
}
