#include "pch.h"
#include "AtominaException.h"

namespace ATMA {

	AtominaException::AtominaException(const std::string &l_message) noexcept : exception(m_msg.c_str()) {
			m_msg = l_message;
	}

	ObjectNotFoundException::ObjectNotFoundException(const std::string &l_message) noexcept : AtominaException(l_message) {
		
	}

	const char *ObjectNotFoundException::what() const noexcept
	{
		return m_msg.c_str();
	}
	

}