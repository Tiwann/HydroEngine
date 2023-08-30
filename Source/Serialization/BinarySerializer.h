#pragma once
#include "Serializer.h"

namespace Hydro
{
    template<typename T>
    class BinarySerializer : public Serializer<T>
    {
    public:
        explicit BinarySerializer(std::string&& filepath);
    private:
        using Super = Serializer<T>;
    };
}
