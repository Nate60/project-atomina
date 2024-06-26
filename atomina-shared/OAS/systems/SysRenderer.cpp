
#include "pch.hpp"
#include "SysRenderer.hpp"

namespace ATMA
{

    SysRenderer::SysRenderer(): SysBase(SystemType(System::Renderer), "Renderer")
    {
        m_req.set(AttrType(Attribute::Render));
    }

    SysRenderer::~SysRenderer() {}

    void SysRenderer::update(const long long &l_dt) {}

    void SysRenderer::notify(const ObjectEventContext &l_e) {}


    bool SysRenderer::addObject(const ObjectId &l_id)
    {
        if(std::count(m_objects.begin(), m_objects.end(), l_id))
        {
            ATMA_ENGINE_WARN(
                "Unable to add object id: {0:d} as it already exists in system: {1:d} ",
                l_id,
                getType()
            );
            return false;
        }
        auto &ctx = ATMAContext::getContext();
        auto attr = ctx.getAttribute<AttrRenderable>(l_id, AttributeType(Attribute::Render));
        m_renderIDs[l_id] = ctx.m_renderCtx->add(attr);
        m_objects.push_back(l_id);
        ATMA_ENGINE_INFO("Added object id: {0:d} to system: {1} ", l_id, shared_from_this());
        return true;
    }

    bool SysRenderer::removeObject(const ObjectId &l_id)
    {
        auto &ctx = ATMAContext::getContext();
        for(auto it = m_objects.begin(); it != m_objects.end(); it++)
        {
            if(*it == l_id)
            {
                m_objects.erase(it);
                ctx.m_renderCtx->remove(m_renderIDs[l_id]);
                m_renderIDs.erase(m_renderIDs.find(l_id));
                ATMA_ENGINE_INFO(
                    "Removed object id: {0:d} from system: {1} ", l_id, shared_from_this()
                );
                return true;
            }
        }
        ATMA_ENGINE_WARN(
            "Unable to remove object id: {0:d} in system: {1:d} as it does not exist",
            l_id,
            getType()
        );
        return false;
    }

}
