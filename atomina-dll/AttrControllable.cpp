#include "pch.h"
#include "AttrControllable.h"

namespace ATMA
{
	AttrControllable::AttrControllable(): AttrBase(static_cast<AttributeType>(Attribute::Controllable))
	{}

	AttrControllable::~AttrControllable()
	{}

	void AttrControllable::readIn(std::stringstream &l_stream)
	{}
}


