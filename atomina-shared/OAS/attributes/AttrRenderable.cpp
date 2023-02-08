#include "pch.hpp"
#include "AttrRenderable.hpp"

namespace ATMA
{

    AttrRenderable::AttrRenderable(): AttrBase(AttrType(Attribute::Renderable), "Renderable") {}

    AttrRenderable::~AttrRenderable() {}

    void AttrRenderable::readIn(std::stringstream &l_stream) {}

}