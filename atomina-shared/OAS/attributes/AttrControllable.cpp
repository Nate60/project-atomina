#include "pch.hpp"
#include "AttrControllable.hpp"

namespace ATMA
{
    AttrControllable::AttrControllable(): AttrBase(AttrType(Attribute::Controllable), "Controllable") {}

    AttrControllable::~AttrControllable() {}

    void AttrControllable::readIn(std::stringstream &l_stream) {}
}
