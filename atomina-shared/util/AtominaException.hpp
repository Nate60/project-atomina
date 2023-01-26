#pragma once
#include "core/api.hpp"
#include "pch.hpp"

namespace ATMA
{

    /*
     * Abstract Exception class, provides basic constructor and message storage
     * No default constructor is provided
     */
    class ATMA_API AtominaException: public std::runtime_error
    {
    public:
        AtominaException(const std::string &l_message) noexcept: runtime_error(l_message) {}
    };

    /**
     * Exception to be thrown when an error occurs when registering an id or related object to
     * a manager
     */
    struct ATMA_API RegistrationException: public AtominaException
    {

        RegistrationException(const std::string &l_message) noexcept: AtominaException(l_message) {}
    };

    /**
     * Exception to be thrown when a value cannot be found and cannot recover
     */
    struct ATMA_API ValueNotFoundException: public AtominaException
    {

        ValueNotFoundException(const std::string &l_message) noexcept: AtominaException(l_message)
        {
        }
    };

    /**
     * Exception thrown when the logger engine has not been initialized
     */
    struct ATMA_API LoggerNotInitializedException: public AtominaException
    {
        LoggerNotInitializedException(const std::string &l_message) noexcept:
            AtominaException(l_message)
        {
        }
    };

    /**
     * Exception thrown when acquisition of resources fails
     */

    struct ATMA_API ResourceAcquisitionException: public AtominaException
    {
        ResourceAcquisitionException(const std::string &l_message) noexcept:
            AtominaException(l_message)
        {
        }
    };

    /**
     * exception for network related errors
     */
    struct ATMA_API NetworkException: public AtominaException
    {
        NetworkException(const std::string &l_message) noexcept: AtominaException(l_message) {}
    };

}
