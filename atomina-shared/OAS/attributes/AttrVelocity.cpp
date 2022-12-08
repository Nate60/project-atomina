#include "pch.hpp"
#include "AttrVelocity.hpp"

namespace ATMA
{

    AttrVelocity::AttrVelocity():
        AttrBase(AttrType(Attribute::Velocity), "Velocity"),
        m_dx(0.0f),
        m_dy(0.0f)
    {
    }

    AttrVelocity::~AttrVelocity() {}

    void AttrVelocity::readIn(std::stringstream &l_stream) {}

}