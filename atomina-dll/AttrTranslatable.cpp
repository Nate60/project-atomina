#include "pch.h"
#include "AttrTranslatable.h"

namespace ATMA {

	AttrTranslatable::AttrTranslatable() : AttrBase(Attribute::Translatable), type_(Attribute::Translatable), x_(0.0f), y_(0.0f), dx_(0.0f), dy_(0.0f) {

	}

	AttrTranslatable::~AttrTranslatable() {

	}

	void AttrTranslatable::readIn(std::stringstream& l_stream) {

	}

}