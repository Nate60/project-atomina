#include "core/ATMAContext.hpp"
#include "pch.hpp"
#include "SysTranslator.hpp"
#include "../AttributeManager.hpp"

namespace ATMA
{

    SysTranslator::SysTranslator(): SysBase(SystemType(System::Translator), "Translator")
    {
        m_req.push_back(std::bitset<ATConst::BITSET_SIZE>{});
        m_req[0].set(AttrType(Attribute::Shape));
        m_req[0].set(AttrType(Attribute::Velocity));
    }

    SysTranslator::~SysTranslator() {}

    void SysTranslator::update(ATMAContext *l_ctx, const double &l_dt)
    {
        auto step = l_dt / 1000000.f;
        for(auto &obj: m_objects)
        {
            std::shared_ptr<AttrShape> attrPos =
                l_ctx->m_attrMan->getAttribute<AttrShape>(obj.second, AttrType(Attribute::Shape));
            std::shared_ptr<AttrVelocity> attrVel =
                l_ctx->m_attrMan->getAttribute<AttrVelocity>(obj.second, AttrType(Attribute::Velocity));
            attrPos->m_pos.x += attrVel->m_dpos.x * step;
            attrPos->m_pos.y += attrVel->m_dpos.y * step;
            attrPos->m_rot += attrVel->m_drot * step;
        }
    }

    void SysTranslator::notify(ATMAContext *l_ctx, const ObjectEventContext &l_e) {}

}
