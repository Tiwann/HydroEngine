#pragma once
#include "SharedPointer.h"

namespace Hydro
{
    class VertexArray;
}

namespace Hydro
{
    enum class VertexAttributeType
    {
        Float,
        Vector2,
        Vector3,
        Vector4,
        Matrix4
    };
    
    struct VertexAttribute
    {
        std::string Name;
        VertexAttributeType Type;

        bool operator==(const VertexAttribute&) const;
    };

    uint32_t GetNumComponents(VertexAttributeType Type);
    
    class VertexBufferLayout
    {
    public:
        VertexBufferLayout(const std::vector<VertexAttribute>& Attributes);
        void AddAttribute(const VertexAttribute& Attribute);
        void Apply(const Ref<VertexArray>& Vao) const;
        
        size_t Count() const;
        size_t Stride() const;
        size_t GetOffset(const VertexAttribute& Attribute) const;
        

        VertexAttribute& operator[](size_t Index);
        const VertexAttribute& operator[](size_t Index) const;
        constexpr std::vector<VertexAttribute>::iterator begin() { return m_Attributes.begin(); }
        constexpr std::vector<VertexAttribute>::iterator end() { return m_Attributes.end(); }

        static VertexBufferLayout Default;
    private:
        std::vector<VertexAttribute> m_Attributes;
    };
}
