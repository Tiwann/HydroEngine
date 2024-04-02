#pragma once
#include "Model.h"
#include "SharedPointer.h"
#include "Filesystem.h"

namespace Hydro
{
    class MeshImporter
    {
    public:
        MeshImporter() = default;
        virtual Ref<Mesh> Load(const Path& Filepath) = 0;
    };
}
