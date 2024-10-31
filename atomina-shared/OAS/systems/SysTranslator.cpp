#include "pch.hpp"
#include "SysTranslator.hpp"

namespace ATMA
{

    SysTranslator::SysTranslator(): SysBase(SystemType(System::Translator), "Translator")
    {
        m_req.push_back(std::bitset<ATConst::OBJECT_BIT_SIZE>{});
        m_req[0].set(AttrType(Attribute::Shape));
        m_req[0].set(AttrType(Attribute::Velocity));
    }

    SysTranslator::~SysTranslator() {}

    void SysTranslator::update(const long long &l_dt)
    {
        auto step = l_dt / 1000000.f;
        m_stopwatch.start();
        for(auto &obj: m_objects)
        {
            std::shared_ptr<AttrShape> attrPos =
                ATMAContext::getContext().getAttribute<AttrShape>(obj.second, AttrType(Attribute::Shape));
            std::shared_ptr<AttrVelocity> attrVel =
                ATMAContext::getContext().getAttribute<AttrVelocity>(
                    obj.second, AttrType(Attribute::Velocity)
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