#include "pch.h"
#include "AttrBase.h"

namespace ATMA {

	Attribute AttrBase::getType() const {
		return m_type;
	}

	std::stringstream& operator >> (std::stringstream& l_stream, AttrBase& b) {
		return l_stream;
	}

}