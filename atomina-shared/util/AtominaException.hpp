#pragma once
#include "core/api.hpp"
#include "pch.hpp"

namespace ATMA
{

    /*
     * Abstract Exception class, provides basic constructor and message storage
     * No default constructor is provided
     */
    class AtominaException: public std::runtime_error
    {
    public:
        AtominaException(const std::string &l_message) noexcept: runtime_error(l_message) {}
    };

    /**
     * Exception to be thrown when an error occurs when registering an id or related object to
     * a manager
     */
    struct RegistrationException: public AtominaException
    {

        RegistrationException(const std::string &l_message) noexcept: AtominaException(l_message) {}
    };

    /**
     * Exception to be thrown when a value cannot be found and cannot recover
     */
    struct ValueNotFoundException: public AtominaException
    {

        ValueNotFoundException(const std::string &l_message) noexcept: AtominaException(l_message)
        {
        }
    };

    /**
     * Exception thrown when the logger engine has not been initialized
     */
    struct InitializationException: public AtominaException
    {
        InitializationException(const std::string &l_message) noexcept: AtominaException(l_message)
        {
        }
    };

    /**
     * Exception thrown when acquisition of resources fails
     */

    struct ResourceAcquisitionException: public AtominaException
    {
        ResourceAcquisitionException(const std::string &l_message) noexcept:
            AtominaException(l_message)
        {
        }
    };

    /**
     * exception for network related errors
     */
    struct NetworkException: public AtominaException
    {
        NetworkException(const std::string &l_message) noexcept: AtominaException(l_message) {}
    };

    /**
     * exception for Serialization and Deserialization
     */
    struct SerializationException : public AtominaException
    {
        SerializationException(const std::string &l_message) noexcept: AtominaException(l_message)
        {
        }
    };


    /**
    * exception for timer related errors
    */
    struct TimeException : public AtominaException
    {
        TimeException(const std::string &l_message) noexcept: AtominaException(l_message) {}
    };
}
