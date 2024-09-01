#pragma once
#include "Core/VertexArray.h"
#include "Core/Types.h"


namespace Hydro
{
    class OpenGLVertexArray : public VertexArray
    {
    public:
        OpenGLVertexArray();
        ~OpenGLVertexArray() override;
        void Bind() const override;
        void Unbind() const override;
        void SetBufferLayout(const VertexBufferLayout& Layout) override;
    private:
        uint32 m_Handle;
    };
}
