#include "pch.hpp"
#include "AttrShape.hpp"

namespace ATMA
{

    AttrShape::AttrShape(): AttrBase(AttrType(Attribute::Shape), "Shape") {}

    AttrShape::~AttrShape() {}

    void AttrShape::readIn(std::stringstream &l_stream) {}

}