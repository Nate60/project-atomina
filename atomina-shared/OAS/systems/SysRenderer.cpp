
#include "pch.hpp"
#include "SysRenderer.hpp"

namespace ATMA
{

    static const unsigned int RENDER_PATTERN = 0u;
    static const unsigned int TEXT_PATTERN = 1u;
    static const unsigned int SPRITE_PATTERN = 2u;

    SysRenderer::SysRenderer(): SysBase(SystemType(System::Renderer), "Renderer")
    {
        m_req.push_back(std::bitset<ATConst::OBJECT_BIT_SIZE>{});
        m_req.push_back(std::bitset<ATConst::OBJECT_BIT_SIZE>{});
        m_req.push_back(std::bitset<ATConst::OBJECT_BIT_SIZE>{});
        m_req[RENDER_PATTERN].set(AttrType(Attribute::Render));
        m_req[TEXT_PATTERN].set(AttrType(Attribute::Text));
        m_req[SPRITE_PATTERN].set(AttrType(Attribute::Sprite));
    }

    SysRenderer::~SysRenderer() {}

    void SysRenderer::update(const long long &l_dt) {
        m_stopwatch.start();
        auto &ctx = ATMAContext::getContext();
        auto renderer = ctx.getRenderer();
        for(auto &id: m_objects)
        {
            switch(id.first){
            case RENDER_PATTERN:
                {
                    auto attr = ctx.getAttribute<AttrRenderable>(id.second, AttributeType(Attribute::Render));
                    renderer->addElement(attr->m_self);
                    break;
                }
            case TEXT_PATTERN:
                {
                    auto attr = ctx.getAttribute<AttrText>(id.second, AttributeType(Attribute::Text));
                    renderer->addElement(attr->m_self);
                    break;
                }
            case SPRITE_PATTERN:
                {
                    auto attr = ctx.getAttribute<AttrSprite>(id.second, AttributeType(Attribute::Sprite));
                    renderer->addElement(attr->m_self);
                    break;
                }
            }
          
        }
        m_stopwatch.stop();
        m_stopwatch.reset();

    }

    void SysRenderer::notify(const ObjectEventContext &l_e) {}

}
