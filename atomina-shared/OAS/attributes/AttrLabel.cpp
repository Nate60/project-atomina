#include "AttrLabel.hpp"

namespace ATMA
{

    AttrLabel::AttrLabel(): AttrBase(AttributeType(Attribute::Label), "Label") {}

    AttrLabel::~AttrLabel() {}

    void AttrLabel::readIn(std::stringstream &l_stream) {}

}