#include "pch.hpp"
#include "AttrRenderable.hpp"

namespace ATMA
{

	AttrRenderable::AttrRenderable():AttrBase(AttrType(Attribute::Render), "Renderable")
	{}

	AttrRenderable::~AttrRenderable() {}

	void AttrRenderable::readIn(std::stringstream &l_stream){}

}