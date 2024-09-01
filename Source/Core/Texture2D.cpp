#include "Texture2D.h"

#include "Assertion.h"
#include "Platform/PlatformTexture2D.h"

#include "Log.h"
#include "LogVerbosity.h"
#include "Macros.h"
#include "Sprite.h"
#include "SpriteAnimation.h"
#include "SpriteSheet.h"

#include "Math/Vector2.h"

namespace Hydro
{
    Texture2D::Texture2D(std::string Name, uint32 Width, uint32 Height, const TextureParams& Params, uint32 Slot) : m_Name(std::move(Name)),
        m_Width(Width), m_Height(Height), m_Slot(Slot), m_Params(Params)
    {
        
    }
    
    
    Ref<Texture2D> Texture2D::Create(const std::string& Name, uint32 Width, uint32 Height, const TextureParams& Params, uint32 Slot)
    {
        HYDRO_RHI_PLATFORM_RETURN(Texture2D, Name, Width, Height, Params, Slot);
    }

    Ref<Texture2D> Texture2D::CreateFromFile(const std::string& Name, const Path& Filepath, const TextureParams& Params, uint32 Slot)
    {
        Ref<Texture2D> Texture = Create(Name, 0, 0, Params, Slot);
        ScopedBuffer RawImageData = File::ReadToBuffer(Filepath);
        
        const Ref<Image> ImageData = CreateRef<Image>(RawImageData.AsBuffer(), ImageFormat::RGBA8);
        Texture->SetData(ImageData);
        return Texture;
    }

    Vector2 Texture2D::GetSize() const
    {
        return {(float)m_Width, (float)m_Height};
    }

    uint32 Texture2D::GetSlot() const
    {
        return m_Slot;
    }

    void Texture2D::SetSlot(uint32 Slot)
    {
        m_Slot = Slot;
    }

    Sprite Texture2D::CreateSprite(const Vector2& Position, const Vector2& Size)
    {
        HYDRO_ASSERT(Position.x >= 0 && Position.x < (float)m_Width &&
                    Position.y >= 0 && Position.y < (float)m_Height &&
                    Position.x + Size.x <= (float)m_Width && 
                    Position.y + Size.y <= (float)m_Height, "Failed to created sprite");

        return { shared_from_this(), Position, Size };
    }

    Sprite Texture2D::CreateSprite()
    {
        return { shared_from_this(), Vector2::Zero, GetSize() };
    }

    Ref<SpriteAnimation> Texture2D::CreateAnimation(uint32 NumRows, uint32 NumColumns, uint32 NumSprites, uint32 SpriteSize)
    {
        Ref<SpriteAnimation> Result = SpriteAnimation::Create();

        uint32 Processed = 0;
        for(uint32 Row = 0; Row < NumRows; Row++)
        {
            if(Processed >= NumSprites) break;
            for(uint32 Column = 0; Column < NumColumns; Column++)
            {
                if(Processed >= NumSprites) break;
                const Vector2 Position = {(float)(Column * SpriteSize), (float)(Row * SpriteSize)};
                const Vector2 Size = Vector2::One * (float)SpriteSize;
                Sprite Sprite = CreateSprite(Position, Size);
                Result->AddSprite(Sprite);
                Processed++;
            }
        }
        return Result;
    }

    Ref<SpriteAnimation> Texture2D::CreateAnimation(const SpriteSheet& SpriteSheet)
    {
        return CreateAnimation(SpriteSheet.NumRows,
                               SpriteSheet.NumColumns,
                               SpriteSheet.NumSprites,
                               SpriteSheet.SpriteSize);
    }
}
