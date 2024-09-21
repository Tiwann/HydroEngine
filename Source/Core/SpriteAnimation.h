#pragma once
#include "Filesystem.h"
#include "SharedPointer.h"
#include "Containers/DynamicArray.h"
#include "AnimationNotify.h"
#include "Containers/ArrayView.h"

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
        
        Array<Sprite>::SizeType Count() const;
        Sprite& GetSprite(size_t Index);


        void AddNotify(const AnimationNotify& Notify);
        const Array<AnimationNotify>& GetNotifies() const;
    private:
        Array<Sprite> m_Sprites;
        Array<AnimationNotify> m_Notifies;
    };
}
