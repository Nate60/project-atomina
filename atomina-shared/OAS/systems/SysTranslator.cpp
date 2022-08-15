#include "pch.hpp"
#include "SysTranslator.hpp"

namespace ATMA
{

    SysTranslator::SysTranslator(): SysBase(SystemType(System::Translator))
    {
        std::bitset<ATConst::OBJECT_BIT_SIZE> bits;
        bits.set((int)Attribute::Translatable);
        m_req = bits;
    }

    SysTranslator::~SysTranslator() {}

    void SysTranslator::update(const float &l_dt)
    {
        for(auto &obj: m_objects)
        {
            std::shared_ptr<AttrTranslatable> attr =
                ATMAContext::getContext().getAttribute<AttrTranslatable>(
                    obj, AttrType(Attribute::Translatable)
                );
            attr->m_x += attr->m_dx * l_dt;
            attr->m_y += attr->m_dy * l_dt;
        }
    }

}