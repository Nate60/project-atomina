#include "pch.hpp"
#include "SysRenderer.hpp"

namespace ATMA
{

    SysRenderer::SysRenderer(): SysBase(SystemType(System::Renderer), "Renderer")
    {
        m_req.set(AttrType(Attribute::Graphic));
    }

    void SysRenderer::update(const float &l_dt) {}

    void SysRenderer::draw(sf::RenderTarget &l_target, const sf::RenderStates &l_states) const
    {
        auto &context = ATMAContext::getContext();
        for(auto &obj: m_objects)
        {
            std::shared_ptr<AttrGraphic> drawable =
                context.getAttribute<AttrGraphic>(obj, AttrType(Attribute::Graphic));
            drawable->draw(l_target, l_states);
        }
    }

    void SysRenderer::notify(const ObjectEventContext &l_e) {}

}