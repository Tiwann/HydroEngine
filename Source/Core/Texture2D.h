#pragma once
#include "Image.h"
#include "SharedPointer.h"
#include "LogCategory.h"
#include "SpriteSheet.h"


HYDRO_DECLARE_LOG_CATEGORY_STATIC(Texture2D, "TEXTURE2D");

namespace Hydro
{
    class Image;
    class Vector2;
    class Sprite;
    class SpriteAnimation;
    struct SpriteSheet;

    enum class TextureFilter
    {
        Nearest,
        Linear,
    };

    enum class TextureWrap
    {
        Clamp,
        Repeat,
        Mirror,
    };

    struct TextureParams
    {
        TextureFilter Filter;
        TextureWrap Wrap;

        TextureParams& WithFilter(TextureFilter NewFilter)
        {
            Filter = NewFilter;
            return *this;
        }

        TextureParams& WithWrap(TextureWrap NewWrap)
        {
            Wrap = NewWrap;
            return *this;
        }
    };
    
    class Texture2D : public std::enable_shared_from_this<Texture2D>
    {
    public:
        Texture2D(std::string Name, uint32_t Width, uint32_t Height, const TextureParams& Params, uint32_t Slot = 0);
        virtual ~Texture2D() = default;

        
        static Ref<Texture2D> Create(const std::string& Name, uint32_t Width, uint32_t Height, const TextureParams& Params, uint32_t Slot = 0);
        static Ref<Texture2D> CreateFromFile(const std::string& Name, const Path& Filepath, const TextureParams& Params, uint32_t Slot = 0);

        virtual void SetTextureParameters(const TextureParams& Params) = 0;
        virtual void SetData(uint8_t* Data, uint32_t Width, uint32_t Height, ImageFormat Format) = 0;
        virtual void SetData(const Ref<Image>& Image) = 0;
        virtual Ref<Image> GetImage() const = 0;
        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;
        
        Vector2 GetSize() const;
        uint32_t GetSlot() const;
        void SetSlot(uint32_t Slot);

        virtual uintptr_t GetHandle() const = 0;

        template<typename T, typename = std::enable_if_t<std::is_convertible_v<T, void*>>>
        T As() const { return (T)GetHandle(); }


        Sprite CreateSprite(const Vector2& Position, const Vector2& Size);
        Sprite CreateSprite();
        Ref<SpriteAnimation> CreateAnimation(uint32_t NumRows, uint32_t NumColumns, uint32_t NumSprites, uint32_t SpriteSize);
        Ref<SpriteAnimation> CreateAnimation(const SpriteSheet& SpriteSheet);
    protected:
        std::string m_Name;
        uint32_t m_Width{0}, m_Height{0};
        uint32_t m_Slot{0};
        ImageFormat m_Format{ImageFormat::RGBA8};
        TextureParams m_Params;
    };
}
