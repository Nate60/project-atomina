#include "pch.hpp"
#include "core/ATMAContext.hpp"
#include "SysRenderer.hpp"
#include "render/Renderer.hpp"
#include "../AttributeManager.hpp"
#include "util/ATConst.hpp"
#include <limits>

namespace ATMA
{

    SysRenderer::SysRenderer(): SysBase(SystemType(System::Renderer), "Renderer")
    {
        m_req.push_back(std::bitset<ATConst::BITSET_SIZE>{});
        m_req[0].set(AttrType(Attribute::Renderable));
    }

    SysRenderer::~SysRenderer() {}

    void SysRenderer::update(ATMAContext *l_ctx, const double &l_dt) {}

    void SysRenderer::notify(ATMAContext *l_ctx, const ObjectEventContext &l_e) {}

    bool SysRenderer::addObject(ATMAContext *l_ctx, const ObjectId &l_id, const unsigned int &l_patternID)
    {
        if(hasObject(l_id) >= 0)
        {
            ATMA_ENGINE_WARN("Unable to add object id: {0:d} as it already exists in system: {1:d} ", l_id, getType());
            return false;
        }
        m_objects.push_back(std::make_pair(l_patternID, l_id));
        ATMA_ENGINE_INFO("Added object id: {0:d} to SysRenderer", l_id);
        l_ctx->m_renderer->addElement(l_id);
        return true;
    }

    bool SysRenderer::removeObject(ATMAContext *l_ctx, const ObjectId &l_id)
    {
        for(auto itr = m_objects.begin(); itr != m_objects.end(); itr++)
        {
            if(itr->second == l_id)
            {
                m_objects.erase(itr);
                ATMA_ENGINE_INFO("Removed object id: {0:d} from system: {1} ", l_id, getType());
                return true;
            }
        }
        ATMA_ENGINE_WARN("Unable to remove object id: {0:d} in system: {1:d} as it does not exist", l_id, getType());
        l_ctx->m_renderer->removeElement(l_id);
        return false;
    }

}
