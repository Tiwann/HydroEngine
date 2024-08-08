#pragma once
#include "Core/Filesystem.h"
#include "Core/SharedPointer.h"


namespace Hydro
{
    template<class T>
    class ResourceManager
    {
    protected:
        ResourceManager() = default;
    public:
        virtual ~ResourceManager() = default;
        virtual Ref<T> Load(const std::string& Name, const Path& Filepath) = 0;
        virtual Ref<T> Retrieve(const std::string& Name) = 0;

        void UnloadAll()
        {
            for (auto& Pair : m_Data)
            {
                Pair.second.reset();
            }
        }
    protected:
        std::unordered_map<std::string, Ref<T>> m_Data;
    };
}
