#include "../../pch.hpp"
#include "AttrControllable.hpp"

namespace ATMA
{
	AttrControllable::AttrControllable(): AttrBase(static_cast<AttributeType>(Attribute::Controllable))
	{}

	AttrControllable::~AttrControllable()
	{}

	void AttrControllable::readIn(std::stringstream &l_stream)
	{}
}


