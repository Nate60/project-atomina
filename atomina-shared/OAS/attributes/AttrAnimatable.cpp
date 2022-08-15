#include "pch.hpp"
#include "AttrAnimatable.hpp"

namespace ATMA
{

    AttrAnimatable::AttrAnimatable(): AttrBase(AttrType(Attribute::Animatable)) {}

    AttrAnimatable::~AttrAnimatable() {}

    void AttrAnimatable::readIn(std::stringstream &l_stream) {}

}