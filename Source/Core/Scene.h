#pragma once
#include "LogCategory.h"
#include "SharedPointer.h"
#include "Core/Log.h"
#include "GUID.h"


HYDRO_DECLARE_LOG_CATEGORY_STATIC(Scene, "SCENE");

class b2World;

namespace Hydro
{
    class GameObject;
    
    class Scene
    {
    public:
        Scene();
        HYDRO_NO_COPYABLE_NO_MOVABLE(Scene);
        
        void OnInit();
        void OnUpdate(float Delta) const;
        void OnDestroy() const;
        
        Ref<GameObject> CreateObject(const std::string& Name);
        bool Destroy(Ref<GameObject>& Object);
        void SetName(const std::string& Name);

    private:
        friend class Collider2D;
        GUID m_Guid;
        std::string m_Name;
        std::vector<Ref<GameObject>> m_GameObjects;
        bool m_Enabled;
        b2World* m_Physics2DWorld;
    };
}
