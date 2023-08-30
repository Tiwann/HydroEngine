#pragma once
#include <unordered_map>

#include "Macros.h"
#include "SharedPointer.h"

namespace Hydro
{
    class HYDRO_API SceneObject
    {

    public:
        std::string_view GetName() const;

        static Ref<SceneObject> CreateEmpty(const std::string& name);
    private:
        std::string m_Name;
    };
}
