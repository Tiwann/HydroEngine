#include "HydroPCH.h"
#include "Scene.h"

#include "Application.h"
#include "GameObject.h"
#include "Physics2D.h"
#include "Time.h"
#include "box2d/box2d.h"
#include "Components/Transform.h"


#include <Jolt/RegisterTypes.h>
#include <Jolt/Core/Memory.h>
#include <Jolt/Physics/PhysicsSystem.h>

namespace Hydro
{
    Scene::Scene(): m_Enabled(false), m_Physics2DWorld(nullptr), m_Physics3DWorld(nullptr)
    {
    }

    Scene::~Scene()
    {
        
    }

    void Scene::OnInit()
    {
        m_Physics2DWorld = new b2World(Physics2D::Gravity);

        JPH::RegisterDefaultAllocator();
        JPH::Factory::sInstance = new JPH::Factory;
        JPH::RegisterTypes();
        
        m_Physics3DWorld = new JPH::PhysicsSystem;
        //m_Physics3DWorld->Init(UINT16_MAX, 0, UINT16_MAX, 10240, )
    
        m_RendererBackend = Application::GetCurrentApplication().GetRendererBackend();
        
        for(const Ref<GameObject>& Object : m_GameObjects)
        {
            Object->OnInit();
        }
    }

    void Scene::OnUpdate(float Delta) const
    {
        for(const Ref<GameObject>& Object : m_GameObjects)
        {
            Object->OnUpdate(Delta);
        }

        m_Physics2DWorld->Step(Physics2D::TimeStep * Time::Scale, 8, 3);

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
        delete m_Physics2DWorld;

        delete m_Physics3DWorld;
        JPH::UnregisterTypes();
        delete JPH::Factory::sInstance;
    }
    
    bool Scene::DestroyObject(Ref<GameObject>& Object)
    {
        Object->OnDestroy();
        m_GameObjects.erase(std::ranges::find(m_GameObjects, Object));
        Object.reset();
        return true;
    }

    void Scene::SetName(const std::string& Name)
    {
        m_Name = Name;
    }
}
