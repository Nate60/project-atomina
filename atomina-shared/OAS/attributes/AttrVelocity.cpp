#include "pch.hpp"
#include "AttrVelocity.hpp"

namespace ATMA
{

    AttrVelocity::AttrVelocity(): AttrBase(AttrType(Attribute::Velocity), "Velocity") {}

    AttrVelocity::~AttrVelocity() {}

    void AttrVelocity::readIn(std::stringstream &l_stream) {}

}