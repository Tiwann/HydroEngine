#pragma once
#include "Macros.h"
#include "Core/MeshImporter.h"
#include "Core/Log.h"

HYDRO_DECLARE_LOG_CATEGORY_STATIC(FbxMeshImporter, "FBX")

namespace Hydro
{
    class FbxMeshImporter : public MeshImporter
    {
    public:
        FbxMeshImporter() = default;
        virtual ~FbxMeshImporter() = default;
        HYDRO_NO_COPYABLE_NO_MOVABLE(FbxMeshImporter);
        
        Ref<Mesh> Load(const Path& Filepath) override;
    };
}
