#include "pch.hpp"
#include "OAS/attributes/AttrRenderable.hpp"
#include "core/ATMAContext.hpp"
#include "SysAnimator.hpp"
#include "../AttributeManager.hpp"
#include "util/ATConst.hpp"

namespace ATMA
{

    SysAnimator::SysAnimator(): SysBase(SystemType(System::Animator), "Animator")
    {
        m_req.push_back(std::bitset<ATConst::BITSET_SIZE>{});
        m_req[0].set(AttrType(Attribute::Renderable));
    }

    SysAnimator::~SysAnimator() {}

    void SysAnimator::update(ATMAContext *l_ctx, const double &l_dt)
    {
        for(auto &id: m_objects)
        {
            std::shared_ptr<Renderable> renderable =
                l_ctx->m_attrMan->getAttribute<AttrRenderable>(id.second, AttributeType(Attribute::Renderable))->m_self;
            if(renderable != nullptr)
            {
                for(auto itr = renderable->begin(); itr != renderable->end(); itr++)
                {
                    if(itr->first != nullptr)
                    {
                        itr->first->update(l_dt);
                        itr->second.m_selectAdv = itr->first->getAdv();
                    }
                }
            }
        }
    }

    void SysAnimator::notify(ATMAContext *l_ctx, const ObjectEventContext &l_e) {}
}
