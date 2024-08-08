#include "HydroPCH.h"
#include "Sprite.h"
#include "Texture2D.h"

namespace Hydro
{
    Vector2 Sprite::GetPosition() const
    {
        return m_Position;
    }

    void Sprite::SetPosition(const Vector2& position)
    {
        m_Position = position;
    }

    Vector2 Sprite::GetSize() const
    {
        return m_Size;
    }

    void Sprite::SetSize(const Vector2& size)
    {
        m_Size = size;
    }

    Ref<Texture2D> Sprite::GetTexture() const
    {
        return m_Texture;
    }

    void Sprite::SetTexture(const Ref<Texture2D>& texture)
    {
        m_Texture = texture;
    }
    
}
