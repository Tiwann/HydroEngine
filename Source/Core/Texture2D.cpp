﻿#include "Texture2D.h"

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
    Texture2D::Texture2D(std::string Name, u32 Width, u32 Height, const TextureParams& Params, u32 Slot) : m_Name(std::move(Name)),
        m_Width(Width), m_Height(Height), m_Slot(Slot), m_Params(Params)
    {
        
    }
    
    
    Ref<Texture2D> Texture2D::Create(const std::string& Name, u32 Width, u32 Height, const TextureParams& Params, u32 Slot)
    {
        HYDRO_RHI_PLATFORM_RETURN(Texture2D, Name, Width, Height, Params, Slot);
    }

    Ref<Texture2D> Texture2D::CreateFromFile(const std::string& Name, const Path& Filepath, const TextureParams& Params, u32 Slot)
    {
        Ref<Texture2D> Texture = Create(Name, 0, 0, Params, Slot);
        Buffer RawImageData = File::ReadToBuffer(Filepath);
        
        const Ref<Image> ImageData = Image::Create(BufferView(RawImageData), ImageFormat::RGBA8);
        Texture->SetData(ImageData);
        return Texture;
    }

    Ref<Texture2D> Texture2D::CreateWhiteTexture(u32 Width, u32 Height)
    {
        constexpr auto Params = TextureParams(TextureFilter::Nearest, TextureWrap::Clamp);
        Ref<Texture2D> Texture = Create("WhiteTexture", Width, Height, Params);
        const size_t Size = (size_t)(Width * Height * 4);
        u8* Data = new u8[Size]{};
        memset(Data, 0xffui8, Size);
        Texture->SetData(Data, Width, Height, ImageFormat::RGBA8);
        delete[] Data;
        return Texture;
    }

    Vector2 Texture2D::GetSize() const
    {
        return {(f32)m_Width, (f32)m_Height};
    }

    u32 Texture2D::GetSlot() const
    {
        return m_Slot;
    }

    void Texture2D::SetSlot(u32 Slot)
    {
        m_Slot = Slot;
    }

    Sprite Texture2D::CreateSprite(const Vector2& Position, const Vector2& Size)
    {
        HYDRO_ASSERT(Position.x >= 0 && Position.x < (f32)m_Width &&
                    Position.y >= 0 && Position.y < (f32)m_Height &&
                    Position.x + Size.x <= (f32)m_Width && 
                    Position.y + Size.y <= (f32)m_Height, "Failed to created sprite");

        return { shared_from_this(), Position, Size };
    }

    Sprite Texture2D::CreateSprite()
    {
        return { shared_from_this(), Vector2::Zero, GetSize() };
    }

    Ref<SpriteAnimation> Texture2D::CreateAnimation(u32 NumRows, u32 NumColumns, u32 NumSprites, u32 SpriteSize)
    {
        Ref<SpriteAnimation> Result = SpriteAnimation::Create();

        u32 Processed = 0;
        for(u32 Row = 0; Row < NumRows; Row++)
        {
            if(Processed >= NumSprites) break;
            for(u32 Column = 0; Column < NumColumns; Column++)
            {
                if(Processed >= NumSprites) break;
                const Vector2 Position = {(f32)(Column * SpriteSize), (f32)(Row * SpriteSize)};
                const Vector2 Size = Vector2::One * (f32)SpriteSize;
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
