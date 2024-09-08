#pragma once
#include "Filesystem.h"
#include "SharedPointer.h"
#include "Core/Containers/DynamicArray.h"

namespace Hydro
{
    class Sprite;
    
    class SpriteAnimation
    {
    public:
        using SpriteArray = Array<Sprite>;
        SpriteAnimation() = default;

        static Ref<SpriteAnimation> Create();
        static Ref<SpriteAnimation> CreateFromFiles(const Path* Filepaths, size_t Count);
        static Ref<SpriteAnimation> CreateFromDirectory(const Path& Directory);
        void ClearSprites();
        void AddSprite(const Sprite& Sprite);
        SpriteArray::SizeType Count() const;
        Sprite& GetSprite(size_t Index);
        
    private:
        SpriteArray m_Sprites;
    };
}
