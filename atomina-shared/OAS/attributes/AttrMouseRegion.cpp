#include "pch.hpp"
#include "AttrMouseRegion.hpp"

namespace ATMA
{

    AttrMouseRegion::AttrMouseRegion(): AttrBase(AttrType(Attribute::MouseRegion), "Mouse Region")
    {
    }

    AttrMouseRegion::~AttrMouseRegion() {}

    void AttrMouseRegion::readIn(std::stringstream &l_stream) {}

}