#pragma once
#include "api.h"
#include "pch.h"

namespace ATMA {


	/*
	* Abstract Exception class, provides basic constructor and message storage
	* No default constructor is provided
	*/
	class ATMA_API AtominaException: public std::exception{

	protected:
		std::string m_msg;
	public:

		AtominaException(const std::string &l_message) noexcept;

		virtual const char *what() const noexcept override = 0;

	};

	class ATMA_API ObjectNotFoundException: public AtominaException {
	public:
		ObjectNotFoundException(const std::string &l_message) noexcept;

		virtual const char *what() const noexcept override;

	};

}

