#pragma once
#include "Renderer.h"
#include "Core/Filesystem.h"

namespace Hydro
{
    struct Submesh;
    class Mesh;
    
    class MeshRenderer : public Renderer
    {
    public:
        MeshRenderer();

        bool LoadMesh(const Path& Filepath);
    protected:
        void OnInit() override;
        void OnDestroy() override;
        void OnEnable() override;
        void OnDisable() override;
        void OnUpdate(float Delta) override;

        
    private:
        Ref<Mesh> m_Mesh;
    };
}
