
#include "pch.hpp"
#include "SysRenderer.hpp"

namespace ATMA
{

    SysRenderer::SysRenderer(): SysBase(SystemType(System::Renderer), "Renderer")
    {
        m_req.set(AttrType(Attribute::Render));
    }

    SysRenderer::~SysRenderer() {}

    void SysRenderer::update(const long long &l_dt) {
        m_stopwatch.start();
        auto &ctx = ATMAContext::getContext();
        for(auto &id: m_objects)
        {
            auto attr = ctx.getAttribute<AttrRenderable>(id, AttributeType(Attribute::Render));
            ctx.m_renderCtx->add(attr);
        }
        m_stopwatch.stop();
        // ATMA_ENGINE_TRACE("Renderer update took {}ms", m_stopwatch.getElapsedDuration()/1000000.0);
        m_stopwatch.reset();

    }

    void SysRenderer::notify(const ObjectEventContext &l_e) {}

}
