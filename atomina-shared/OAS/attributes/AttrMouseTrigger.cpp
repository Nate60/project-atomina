#include "pch.hpp"
#include "AttrMouseTrigger.hpp"

namespace ATMA
{

    AttrMouseTrigger::AttrMouseTrigger(): AttrBase(AttrType(Attribute::MouseTrigger)) {}

    AttrMouseTrigger::~AttrMouseTrigger() {}

    void AttrMouseTrigger::readIn(std::stringstream &l_stream) {}

}