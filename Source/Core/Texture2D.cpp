#include "HydroPCH.h"
#include "Texture2D.h"

#include "Assertion.h"
#include "Platform/PlatformTexture2D.h"

#include "Log.h"
#include "LogVerbosity.h"
#include "Macros.h"
#include "Sprite.h"

#include "Math/Vector2.h"
namespace Hydro

{
    Texture2D::Texture2D(std::string Name, uint32_t Width, uint32_t Height, uint32_t Slot) : m_Name(std::move(Name)),
        m_Width(Width), m_Height(Height), m_Slot(Slot)
    {
        
    }
    
    
    Ref<Texture2D> Texture2D::Create(const std::string& Name, uint32_t Width, uint32_t Height, uint32_t Slot)
    {
        HYDRO_RHI_PLATFORM_RETURN(Texture2D, Name, Width, Height, Slot);
    }

    Ref<Texture2D> Texture2D::CreateFromFile(const std::string& Name, const Path& Filepath, uint32_t Slot)
    {
        Ref<Texture2D> Texture = Create(Name, 0, 0, Slot);
        ScopedBuffer RawImageData = File::ReadToBuffer(Filepath);
        const Ref<Image> ImageData = CreateRef<Image>(RawImageData.AsBuffer(), ImageFormat::RGBA8);
        Texture->SetData(ImageData);
        return Texture;
    }

    Vector2 Texture2D::GetSize() const
    {
        return {(float)m_Width, (float)m_Height};
    }

    uint32_t Texture2D::GetSlot() const
    {
        return m_Slot;
    }

    void Texture2D::SetSlot(uint32_t Slot)
    {
        m_Slot = Slot;
    }

    Sprite Texture2D::CreateSprite(const Vector2& Position, const Vector2& Size)
    {
        HYDRO_ASSERT(Position.x >= 0 && Position.x < (float)m_Width &&
                    Position.y >= 0 && Position.x < (float)m_Height &&
                    Position.x + Size.x >= (float)m_Width && 
                    Position.y + Size.y >= (float)m_Height, "Failed to created sprite");

        return { shared_from_this(), Position, Size };
    }

    Sprite Texture2D::CreateDefaultSprite()
    {
        return { shared_from_this(), Vector2::Zero, GetSize() };
    }
}
