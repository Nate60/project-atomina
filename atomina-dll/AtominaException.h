#pragma once
#include "api.h"

namespace ATMA {


	/*
	* Abstract Exception class, provides basic constructor and message storage
	* No default constructor is provided
	*/
	class ATMA_API AtominaException{

	protected:
		const char* msg_;
	public:

		AtominaException(const char* l_message) noexcept;

		virtual const char* what() = 0;

	};

	class ATMA_API ObjectNotFoundException: public AtominaException {
	public:
		ObjectNotFoundException(const char* l_message);

		const char* what();

	};

	/*
	* Exception to be thrown when a function encounters a parameter with invalid values
	*/
	class ATMA_API InvalidParameterException : public AtominaException {

	public:
		InvalidParameterException(const char* l_message) noexcept;

		const char* what();
	};

	/*
	* Exception to be thrown when an input or output stream is in an invalid state
	*/
	class ATMA_API IOException : public AtominaException {

	public:
		IOException(const char* l_message) noexcept;

		const char* what();

	};

}

