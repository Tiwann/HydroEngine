#include "HydroPCH.h"
#include "ObjMeshImporter.h"

namespace Hydro
{
    Ref<Mesh> ObjMeshImporter::Load(const Path& Filepath)
    {
        const std::string FileContent = File::ReadToString(Filepath);
        std::stringstream Stream(FileContent, std::ios::in);
        if(!Stream.good())
            return nullptr;

        std::string Line;
        while (std::getline(Stream, Line))
        {
            if(Line.starts_with("#")) continue;

            if(Line.starts_with("v"))
            {
                
            }
        }

        return nullptr;
    }
}
