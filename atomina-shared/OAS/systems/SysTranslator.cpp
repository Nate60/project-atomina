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

    void SysTranslator::update(const long long &l_dt)
    {
        auto step = l_dt / 1000000.f;
        m_stopwatch.start();
        for(auto &obj: m_objects)
        {
            std::shared_ptr<AttrShape> attrPos =
                ATMAContext::getContext().getAttribute<AttrShape>(obj, AttrType(Attribute::Shape));
            std::shared_ptr<AttrVelocity> attrVel =
                ATMAContext::getContext().getAttribute<AttrVelocity>(
                    obj, AttrType(Attribute::Velocity)
                );
            attrPos->m_pos.x += attrVel->m_dpos.x * step;
            attrPos->m_pos.y += attrVel->m_dpos.y * step;
            attrPos->m_rot += attrVel->m_drot * step;
        }
        m_stopwatch.stop();
        m_stopwatch.reset();
    }

    void SysTranslator::notify(const ObjectEventContext &l_e) {}

}