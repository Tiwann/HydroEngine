#pragma once
#include "Core/Filesystem.h"
#include "Core/SharedPointer.h"
#include "Core/Containers/Map.h"
#include "Core/Containers/String.h"


namespace Hydro
{
    template<class T>
    class ResourceManager
    {
    protected:
        ResourceManager() = default;
    public:
        using MapType = Map<String, Ref<T>>;
        using PairType = typename MapType::PairType;
        
        virtual ~ResourceManager() = default;
        virtual Ref<T> Load(const String& Name, const Path& Filepath) = 0;
        virtual Ref<T> Retrieve(const String& Name) = 0;

        void UnloadAll()
        {
            for (PairType& Pair : m_Data)
            {
                Pair.Value.reset();
            }
        }
    protected:
        MapType m_Data;
    };
}
