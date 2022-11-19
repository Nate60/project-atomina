#include "pch.hpp"
#include "AttrMouseRegion.hpp"

namespace ATMA{

    AttrMouseRegion::AttrMouseRegion() : AttrBase(AttrType(Attribute::MouseRegion))
    {
    }

    AttrMouseRegion::~AttrMouseRegion() {}

    void AttrMouseRegion::readIn(std::stringstream &l_stream) {}

}