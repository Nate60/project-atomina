#include "OAS/attributes/AttrPosition.hpp"
#include "OAS/attributes/AttrVelocity.hpp"
#include "pch.hpp"
#include "SysTranslator.hpp"

namespace ATMA
{

    SysTranslator::SysTranslator(): SysBase(SystemType(System::Translator), "Translator")
    {
        m_req.set(AttrType(Attribute::Position));
        m_req.set(AttrType(Attribute::Velocity));
    }

    SysTranslator::~SysTranslator() {}

    void SysTranslator::update(const float &l_dt)
    {
        for(auto &obj: m_objects)
        {
            std::shared_ptr<AttrPosition> attrPos =
                ATMAContext::getContext().getAttribute<AttrPosition>(
                    obj, AttrType(Attribute::Position)
                );
            std::shared_ptr<AttrVelocity> attrVel =
                ATMAContext::getContext().getAttribute<AttrVelocity>(
                    obj, AttrType(Attribute::Velocity)
                );
            attrPos->m_x += attrVel->m_dx * l_dt;
            attrPos->m_y += attrVel->m_dy * l_dt;
        }
    }

    void SysTranslator::notify(const ObjectEventContext &l_e) {}

}