#include "pch.h"
#include "AtominaException.h"

namespace ATMA {

	AtominaException::AtominaException(const std::string l_message) noexcept {
			msg_ = l_message;
	}

	ObjectNotFoundException::ObjectNotFoundException(const std::string l_message) : AtominaException(l_message) {

	}

	const std::string ObjectNotFoundException::what() {
		return msg_;
	}

	InvalidParameterException::InvalidParameterException(const std::string l_message) noexcept : AtominaException(l_message) {}

	const std::string InvalidParameterException::what() {
		return msg_;
	}

	IOException::IOException(const std::string l_message) noexcept : AtominaException(l_message) {}

	const std::string IOException::what() {
		return msg_;
	}

}