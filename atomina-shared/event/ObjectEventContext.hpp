#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "util/Props.hpp"

namespace ATMA
{

    using std::string_literals::operator""s;

    /**
     * @brief contains information that is required to handle
     * an object event
     */
    class ObjectEventContext
    {
    public:
        // constructor specifying event type and properties
        ObjectEventContext(const unsigned int &l_objectEventType, const Props &l_props = Props{});

        // default deconstructor
        virtual ~ObjectEventContext();

        const unsigned int m_objectEventType;
        const Props m_properties{};
    };

    // log formatting function
    inline std::ostream &operator<<(std::ostream &os, const ObjectEventContext &e)
    {
        return os << e.m_properties.value_or("name", "[null]"s);
    }

}