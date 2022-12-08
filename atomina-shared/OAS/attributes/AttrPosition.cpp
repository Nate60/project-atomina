#include "pch.hpp"
#include "AttrPosition.hpp"

namespace ATMA
{

    AttrPosition::AttrPosition():
        AttrBase(AttrType(Attribute::Position), "Position"),
        m_x(0.0f),
        m_y(0.0f)
    {
    }

    AttrPosition::~AttrPosition() {}

    void AttrPosition::readIn(std::stringstream &l_stream) {}

}