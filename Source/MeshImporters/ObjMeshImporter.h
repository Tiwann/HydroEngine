#pragma once
#include "Macros.h"
#include "Core/MeshImporter.h"

namespace Hydro
{
    class ObjMeshImporter : public MeshImporter
    {
    public:
        virtual ~ObjMeshImporter() = default;
        HYDRO_NO_COPYABLE_NO_MOVABLE(ObjMeshImporter);
        
        Ref<Mesh> Load(const Path& Filepath) override;
    };
}
