#include "pch.hpp"
#include "SysAnimator.hpp"

namespace ATMA
{

    SysAnimator::SysAnimator(): SysBase(SystemType(System::Animator), "Animator")
    {
        m_req.set(AttrType(Attribute::Graphic));
        m_req.set(AttrType(Attribute::Animation));
    }

    void SysAnimator::update(const float &l_dt)
    {
        auto &ctx = ATMAContext::getContext();
        for(auto obj: m_objects)
        {
            auto &sprite =
                ctx.getAttribute<AttrGraphic>(obj, AttrType(Attribute::Graphic))->m_sprite;
            auto attrAnim = ctx.getAttribute<AttrAnimation>(obj, AttrType(Attribute::Animation));
            attrAnim->m_spriteSheet->updateSprite(attrAnim->m_animation, sprite);
        }
    }

    void SysAnimator::notify(const ObjectEventContext &l_e) {}

}