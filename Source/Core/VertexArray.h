#pragma once
#include "SharedPointer.h"

namespace Hydro
{
    class VertexBufferLayout;
}

namespace Hydro
{
    class VertexArray
    {
    public:
        VertexArray() = default;
        virtual ~VertexArray() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;
        virtual void SetBufferLayout(const VertexBufferLayout& Layout) = 0;
        static Ref<VertexArray> Create();
    };
}
