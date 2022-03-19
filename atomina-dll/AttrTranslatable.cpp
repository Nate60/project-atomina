#include "pch.h"
#include "AttrTranslatable.h"

namespace ATMA {

	AttrTranslatable::AttrTranslatable() : AttrBase(Attribute::Translatable), m_type(Attribute::Translatable), m_x(0.0f), m_y(0.0f), m_dx(0.0f), m_dy(0.0f) {

	}

	AttrTranslatable::~AttrTranslatable() {

	}

	void AttrTranslatable::readIn(std::stringstream& l_stream) {

	}

}