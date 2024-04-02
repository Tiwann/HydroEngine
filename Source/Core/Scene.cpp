#include "HydroPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "Physics2D.h"
#include "box2d/box2d.h"

namespace Hydro
{
    Scene::Scene(): m_Enabled(false), m_Physics2DWorld(nullptr)
    {
    }

    void Scene::OnInit()
    {
        const b2Vec2 Gravity = {Physics2D::Gravity.x, Physics2D::Gravity.y};
        m_Physics2DWorld = new b2World(Gravity);
        
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

        m_Physics2DWorld->Step(Physics2D::TimeStep, 8, 3);

        for(const Ref<GameObject>& Object : m_GameObjects)
        {
            Object->OnPhysicsUpdate(Delta);
        }
    }

    void Scene::OnDestroy() const
    {
        for(const Ref<GameObject>& Object : m_GameObjects)
        {
            Object->OnDestroy();
        }

        delete m_Physics2DWorld;
    }

    Ref<GameObject> Scene::CreateObject(const std::string& Name)
    {
        HYDRO_LOG(Scene, Trace, "Created new object {} to scene {}.", Name, m_Name);
        const Ref<GameObject> NewObject = CreateRef<GameObject>(Name);
        NewObject->m_Scene = this;
        m_GameObjects.push_back(NewObject);
        return NewObject;
    }

    bool Scene::Destroy(Ref<GameObject>& Object)
    {
        m_GameObjects.erase(std::ranges::find(m_GameObjects, Object));
        Object.reset();
        return true;
    }

    void Scene::SetName(const std::string& Name)
    {
        m_Name = Name;
    }
}
