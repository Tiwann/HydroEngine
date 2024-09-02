#pragma once
#include "SpriteRenderer.h"
#include "Core/Component.h"
#include "Core/Timer.h"

#define HYDRO_SPRITE_ANIMATOR_MAX_SPRITES 128

namespace Hydro
{
    class SpriteAnimation;
    
    class SpriteAnimator : public Component
    {
    public:
        SpriteAnimator(Entity* Owner);
        
        void OnInit() override;
        void OnUpdate(f32 Delta) override;
        void OnInspectorGUI(const ImGuiIO& IO) override;

        Ref<SpriteRenderer> GetSpriteRenderer() const;
        void SetSpriteRenderer(const Ref<SpriteRenderer>& SpriteRenderer);

        const Ref<SpriteAnimation>& GetAnimation() const;
        void SetAnimation(const Ref<SpriteAnimation>& Animation);

        void SetSpeed(i32 Speed);
        i32 GetSpeed() const;
    private:
        Timer m_Timer;
        Ref<SpriteRenderer> m_SpriteRenderer;
        Ref<SpriteAnimation> m_Animation;
        i32 m_Speed = 12;
        u32 m_Index = 0;
        void OnSpriteChange();
    };
}
