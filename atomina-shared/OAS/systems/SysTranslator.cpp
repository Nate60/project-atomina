#include "pch.hpp"
#include "SysTranslator.hpp"

namespace ATMA
{

    SysTranslator::SysTranslator(): SysBase(SystemType(System::Translator), "Translator")
    {
        m_req.set(AttrType(Attribute::Shape));
        m_req.set(AttrType(Attribute::Velocity));
    }

    SysTranslator::~SysTranslator() {}

    void SysTranslator::update(const float &l_dt)
    {
        for(auto &obj: m_objects)
        {
            std::shared_ptr<AttrShape> attrPos =
                ATMAContext::getContext().getAttribute<AttrShape>(obj, AttrType(Attribute::Shape));
            std::shared_ptr<AttrVelocity> attrVel =
                ATMAContext::getContext().getAttribute<AttrVelocity>(
                    obj, AttrType(Attribute::Velocity)
                );
            attrPos->m_pos.x += attrVel->m_dpos.x * l_dt;
            attrPos->m_pos.y += attrVel->m_dpos.y * l_dt;
        }
    }

    void SysTranslator::notify(const ObjectEventContext &l_e) {}

}