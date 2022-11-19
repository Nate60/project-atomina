#include "pch.hpp"
#include "AttrAnimation.hpp"

namespace ATMA
{

    AttrAnimation::AttrAnimation(): AttrBase(AttrType(Attribute::Animation)) {}

    AttrAnimation::~AttrAnimation() {}

    void AttrAnimation::readIn(std::stringstream &l_stream) {}

}