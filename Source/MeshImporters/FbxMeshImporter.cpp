#include "HydroPCH.h"
#include "FbxMeshImporter.h"


#include "Core/LogVerbosity.h"

#include <ufbx/ufbx.h>

namespace Hydro
{
    Ref<Mesh> FbxMeshImporter::Load(const Path& Filepath)
    {
        constexpr ufbx_load_opts Options = {  .ignore_animation = true };
        ufbx_error Error;
        ufbx_scene* Scene = ufbx_load_file(Filepath.string().c_str(), &Options, &Error);
        if(!Scene)
        {
            HYDRO_LOG(FbxMeshImporter, Verbosity::Error, "Failed to load mesh from fbx! Path: {}", Filepath.string().c_str());
            HYDRO_LOG(FbxMeshImporter, Verbosity::Error, "Reason: {}", Error.description.data);
            return nullptr;
        }

        Mesh Output;
        for (size_t i = 0; i < Scene->nodes.count; i++) {
            const ufbx_node* Node = Scene->nodes.data[i];
            if (Node->is_root) continue;

            printf("Object: %s\n", Node->name.data);
            
            if (Node->mesh) {
                for(size_t vert = 0; vert < Node->mesh->num_vertices; vert++)
                {
                    
                }
            }
        }

        ufbx_free_scene(Scene);
        return nullptr;
    }
}
