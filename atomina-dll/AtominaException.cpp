#include "AtominaException.h"

namespace ATMA {

	AtominaException::AtominaException(const char* l_message) noexcept {
			msg_ = l_message;
	}

	InvalidParameterException::InvalidParameterException(const char* l_message) noexcept : AtominaException(l_message) {}

	const char* InvalidParameterException::what() {
		return msg_;
	}

	IOException::IOException(const char* l_message) noexcept : AtominaException(l_message) {}

	const char* IOException::what() {
		return msg_;
	}

}