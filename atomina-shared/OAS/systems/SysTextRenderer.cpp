
#include "pch.hpp"
#include "SysTextRenderer.hpp"

namespace ATMA
{

    SysTextRenderer::SysTextRenderer(): SysBase(SystemType(System::TextRenderer), "TextRenderer")
    {
        m_req.set(AttrType(Attribute::Label));
    }

    SysTextRenderer::~SysTextRenderer() {}

    void SysTextRenderer::update(const float &l_dt) {
        auto &ctx = ATMAContext::getContext();
        for(auto &id: m_objects)
        {
            auto attr = ctx.getAttribute<AttrLabel>(id, AttributeType(Attribute::Label));
            ctx.m_renderCtx->drawText(attr->m_text,attr->m_pos, attr->m_size);
        }

    }

    void SysTextRenderer::notify(const ObjectEventContext &l_e) {}

}
