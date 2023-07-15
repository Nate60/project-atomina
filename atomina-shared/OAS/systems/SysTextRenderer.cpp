#include "pch.hpp"
#include "SysTextRenderer.hpp"

namespace ATMA
{

    SysTextRenderer::SysTextRenderer():
        SysBase(SystemType(System::TextRenderer), "TextRenderer"),
        m_ctx(ATMAContext::getContext())
    {
        m_renderer = m_ctx.getRenderer();
        m_req.set(AttrType(Attribute::Text));
    }

    SysTextRenderer::~SysTextRenderer() {}

    void SysTextRenderer::update(const float &l_dt)
    {
        for(auto &id: m_objects)
        {
            auto text = m_ctx.getAttribute<AttrText>(id, AttrType(Attribute::Text));
            m_renderer->drawText(text->m_text, text->m_pos, text->m_size, text->m_rot);
        }
    }

    void SysTextRenderer::notify(const ObjectEventContext &l_e) {}
}
