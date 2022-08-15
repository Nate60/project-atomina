#include "pch.hpp"
#include "AttrTranslatable.hpp"

namespace ATMA
{

    AttrTranslatable::AttrTranslatable():
        AttrBase(AttrType(Attribute::Translatable)),
        m_x(0.0f),
        m_y(0.0f),
        m_dx(0.0f),
        m_dy(0.0f)
    {
    }

    AttrTranslatable::~AttrTranslatable() {}

    void AttrTranslatable::readIn(std::stringstream &l_stream) {}

}