#include "pch.h"
#include "AttrBase.h"

namespace ATMA {

	AttributeType AttrBase::getType() const {
		return m_type;
	}

	std::stringstream& operator >> (std::stringstream &l_stream, AttrBase &b) {
		return l_stream;
	}

}