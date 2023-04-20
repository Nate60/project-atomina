#include "pch.hpp"
#include "AttrText.hpp"

namespace ATMA
{

    AttrText::AttrText(): AttrBase(AttrType(Attribute::Text), "Text") {}

    AttrText::~AttrText() {}

    void AttrText::readIn(std::stringstream &l_stream) {}

}