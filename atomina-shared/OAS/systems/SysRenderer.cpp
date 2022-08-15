#include "pch.hpp"
#include "SysRenderer.hpp"

namespace ATMA
{

    SysRenderer::SysRenderer(): SysBase(SystemType(System::Renderer))
    {
        m_req.set(1);
        m_req.set(2);
    }

    void SysRenderer::update(const float &l_dt) {}

    void SysRenderer::draw(sf::RenderTarget &l_target, const sf::RenderStates &l_states) const
    {
        auto &context = ATMAContext::getContext();
        for(auto &obj: m_objects)
        {
            auto pos =
                context.getAttribute<AttrTranslatable>(obj, AttrType(Attribute::Translatable));
            std::shared_ptr<AttrDrawable> drawable =
                context.getAttribute<AttrDrawable>(obj, AttrType(Attribute::Drawable));
            drawable->updateScreenPosition(pos->m_x, pos->m_y);
            drawable->draw(l_target, l_states);
        }
    }

}