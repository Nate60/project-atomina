#include "pch.h"
#include "AtominaException.h"

namespace ATMA {

	AtominaException::AtominaException(const char* l_message) noexcept {
			msg_ = l_message;
	}

	ObjectNotFoundException::ObjectNotFoundException(const char* l_message) : AtominaException(l_message) {

	}

	const char * ObjectNotFoundException::what() {
		return msg_;
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