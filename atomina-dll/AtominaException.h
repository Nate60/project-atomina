#pragma once
#include "api.h"
#include "pch.h"

namespace ATMA {


	/*
	* Abstract Exception class, provides basic constructor and message storage
	* No default constructor is provided
	*/
	class ATMA_API AtominaException: public std::runtime_error{
	public:

		AtominaException(const std::string &l_message) noexcept: runtime_error(l_message)
		{}

	};

	struct ATMA_API ValueNotFoundException: public AtominaException {

		ValueNotFoundException(const std::string &l_message) noexcept: AtominaException(l_message)
		{}


	};

	struct ATMA_API LoggerNotInitializedException: public AtominaException
	{
		LoggerNotInitializedException(const std::string &l_message) noexcept: AtominaException(l_message)
		{}


	};	

	struct ATMA_API NetworkException: public AtominaException
	{
		NetworkException(const std::string &l_message) noexcept: AtominaException(l_message)
		{}

	};


}

