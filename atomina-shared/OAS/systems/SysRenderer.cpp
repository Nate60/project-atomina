
#include "pch.hpp"
#include "SysRenderer.hpp"

namespace ATMA
{

    SysRenderer::SysRenderer(): SysBase(SystemType(System::Renderer), "Renderer")
    {
        m_req.set(AttrType(Attribute::Render));
    }

    SysRenderer::~SysRenderer() {}

    void SysRenderer::update(const float &l_dt) {
        auto &ctx = ATMAContext::getContext();
        for(auto &id: m_objects)
        {
            auto attr = ctx.getAttribute<AttrRenderable>(id, AttributeType(Attribute::Render));
            ctx.m_renderCtx->draw(attr);
        }

    }

    void SysRenderer::notify(const ObjectEventContext &l_e) {}

}
