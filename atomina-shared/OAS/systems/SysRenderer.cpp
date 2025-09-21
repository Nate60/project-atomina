
#include "pch.hpp"
#include "core/ATMAContext.hpp"
#include "SysRenderer.hpp"
#include "render/GLRenderer.hpp"
#include "../AttributeManager.hpp"
#include "util/ATConst.hpp"

namespace ATMA
{

    static const unsigned int RENDER_PATTERN = 0u;
    static const unsigned int TEXT_PATTERN = 1u;
    static const unsigned int SPRITE_PATTERN = 2u;

    SysRenderer::SysRenderer(): SysBase(SystemType(System::Renderer), "Renderer")
    {
        m_req.push_back(std::bitset<ATConst::BITSET_SIZE>{});
        m_req.push_back(std::bitset<ATConst::BITSET_SIZE>{});
        m_req.push_back(std::bitset<ATConst::BITSET_SIZE>{});
        m_req[RENDER_PATTERN].set(AttrType(Attribute::Render));
        m_req[TEXT_PATTERN].set(AttrType(Attribute::Text));
        m_req[SPRITE_PATTERN].set(AttrType(Attribute::Sprite));
    }

    SysRenderer::~SysRenderer() {}

    void SysRenderer::update(ATMAContext *l_ctx, const double &l_dt)
    {
        m_stopwatch.start();
        for(auto &id: m_objects)
        {
            switch(id.first)
            {
            case RENDER_PATTERN:
                {
                    auto attr =
                        l_ctx->m_attrMan->getAttribute<AttrRenderable>(id.second, AttributeType(Attribute::Render));
                    l_ctx->m_renderer->addElement(attr->m_self);
                    break;
                }
            case TEXT_PATTERN:
                {
                    auto attr = l_ctx->m_attrMan->getAttribute<AttrText>(id.second, AttributeType(Attribute::Text));
                    l_ctx->m_renderer->addElement(attr->m_self);
                    break;
                }
            case SPRITE_PATTERN:
                {
                    auto attr = l_ctx->m_attrMan->getAttribute<AttrSprite>(id.second, AttributeType(Attribute::Sprite));
                    if(l_ctx->m_attrMan->hasAttribute(id.second, AttributeType(Attribute::Animation)))
                    {
                        auto animAttr = l_ctx->m_attrMan->getAttribute<AttrAnimation>(
                            id.second, AttributeType(Attribute::Animation)
                        );
                        animAttr->m_self->update(l_dt);
                        attr->m_self->m_selectPos = animAttr->m_self->m_data.m_startPos + animAttr->m_self->getAdv();
                        attr->m_self->m_selectSize = animAttr->m_self->m_data.m_frameSize;
                    }
                    l_ctx->m_renderer->addElement(attr->m_self);
                    break;
                }
            }
        }
        m_stopwatch.stop();
        m_stopwatch.reset();
    }

    void SysRenderer::notify(ATMAContext *l_ctx, const ObjectEventContext &l_e) {}

}
