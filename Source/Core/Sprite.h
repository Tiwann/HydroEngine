#pragma once
#include "Math/Vector2.h"
#include "SharedPointer.h"

namespace Hydro
{
    class Texture2D;
    
    class Sprite
    {
    public:
        Sprite(const Ref<Texture2D>& Texture, Vector2 Pos, Vector2 Size)
            : m_Position(Pos), m_Size(Size), m_Texture(Texture)
        {
            
        }

        Vector2 GetPosition() const;
        void SetPosition(const Vector2& position);
        
        Vector2 GetSize() const;
        void SetSize(const Vector2& size);
        
        Ref<Texture2D> GetTexture() const;
        void SetTexture(const Ref<Texture2D>& texture);

        static Sprite CreateFromTexture(const Ref<Texture2D>& Texture);
        static Sprite CreateFromTexture(const Ref<Texture2D>& Texture, Vector2 Pos, Vector2 Size);
    private:
        Vector2 m_Position;
        Vector2 m_Size;
        Ref<Texture2D> m_Texture;
    };
}
