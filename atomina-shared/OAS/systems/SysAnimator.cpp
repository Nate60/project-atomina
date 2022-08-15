#include "pch.hpp"
#include "SysAnimator.hpp"

namespace ATMA
{

    SysAnimator::SysAnimator(): SysBase(SystemType(System::Animator))
    {
        m_req.set(AttrType(Attribute::Drawable));
        m_req.set(AttrType(Attribute::Animatable));
    }

    void SysAnimator::update(const float &l_dt)
    {
        auto &ctx = ATMAContext::getContext();
        for(auto obj: m_objects)
        {
            auto &sprite =
                ctx.getAttribute<AttrDrawable>(obj, AttrType(Attribute::Drawable))->m_sprite;
            auto attrAnim = ctx.getAttribute<AttrAnimatable>(obj, AttrType(Attribute::Animatable));
            attrAnim->m_spriteSheet->updateSprite(attrAnim->m_animation, sprite);
        }
    }

}