#include "pch.hpp"
#include "AttrCollidable.hpp"

namespace ATMA
{

    AttrCollidable::AttrCollidable(): AttrBase(AttrType(Attribute::Collidable), "Collidable") {}

    AttrCollidable::~AttrCollidable() {}

    void AttrCollidable::readIn(std::stringstream &l_stream) {}

}