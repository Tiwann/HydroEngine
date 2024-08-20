#pragma once
#include "Filesystem.h"
#include "SharedPointer.h"

namespace Hydro
{
    class Sprite;
    
    class SpriteAnimation
    {
    public:
        SpriteAnimation() = default;

        static Ref<SpriteAnimation> Create();
        static Ref<SpriteAnimation> CreateFromFiles(const Path* Filepaths, size_t Count);
        static Ref<SpriteAnimation> CreateFromDirectory(const Path& Directory);
        void ClearSprites();
        void AddSprite(const Sprite& Sprite);
        size_t Count();
        Sprite& GetSprite(size_t Index);
        
    private:
        std::vector<Sprite> m_Sprites;
    };
}
