#pragma once
#include "api.h"

namespace ATMA {


	/*
	* Abstract Exception class, provides basic constructor and message storage
	* No default constructor is provided
	*/
	class ATMA_API AtominaException{

	protected:
		std::string msg_;
	public:

		AtominaException(const std::string l_message) noexcept;

		virtual const std::string what() = 0;

	};

	class ATMA_API ObjectNotFoundException: public AtominaException {
	public:
		ObjectNotFoundException(const std::string l_message);

		const std::string what();

	};

	/*
	* Exception to be thrown when a function encounters a parameter with invalid values
	*/
	class ATMA_API InvalidParameterException : public AtominaException {

	public:
		InvalidParameterException(const std::string l_message) noexcept;

		const std::string what();
	};

	/*
	* Exception to be thrown when an input or output stream is in an invalid state
	*/
	class ATMA_API IOException : public AtominaException {

	public:
		IOException(const std::string l_message) noexcept;

		const std::string what();

	};

}

