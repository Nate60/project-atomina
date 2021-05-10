#include "AtominaException.h"

namespace ATMA {

	AtominaException::AtominaException(const char* _Message) noexcept {
			msg_ = _Message;
	}

	InvalidParameterException::InvalidParameterException(const char* _Message) noexcept : AtominaException(_Message) {

	}

	const char* InvalidParameterException::what() {
		return msg_;
	}

}