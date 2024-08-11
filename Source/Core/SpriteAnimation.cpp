#include "HydroPCH.h"
#include "SpriteAnimation.h"
#include "Sprite.h"
#include "Texture2D.h"

namespace Hydro
{
    Ref<SpriteAnimation> SpriteAnimation::Create()
    {
        return CreateRef<SpriteAnimation>();
    }

    Ref<SpriteAnimation> SpriteAnimation::CreateFromFiles(const Path* Filepaths, size_t Count)
    {
        Ref<SpriteAnimation> Result = Create();
        for(size_t i = 0; i < Count; i++)
        {
            const Path& Filepath = Filepaths[i];
            constexpr TextureParams Params = {TextureFilter::Nearest, TextureWrap::Clamp};
            const auto& Texture = Texture2D::CreateFromFile("RuntimeLoadedTextureForSpriteAnim", Filepath, Params);
            Result->AddSprite(Sprite::CreateFromTexture(Texture));
        }
        return Result;
    }

    Ref<SpriteAnimation> SpriteAnimation::CreateFromDirectory(const Path& Directory)
    {
        const std::vector<Path> Filepaths = Directory::GetFiles(Directory);
        return CreateFromFiles(Filepaths.data(), Filepaths.size());
    }

    void SpriteAnimation::AddSprite(const Sprite& Sprite)
    {
        m_Sprites.push_back(Sprite);
    }

    size_t SpriteAnimation::Count()
    {
        return m_Sprites.size();
    }

    Sprite& SpriteAnimation::GetSprite(size_t Index)
    {
        return m_Sprites[Index];
    }
}
