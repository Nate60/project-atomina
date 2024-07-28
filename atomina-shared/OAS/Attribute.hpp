#pragma once
#include "core/api.hpp"

namespace ATMA
{

    using AttributeType = unsigned int;

    /**
     * enumeration of all attribute types
     */
    enum class Attribute
    {
        None = 0,
        Shape,
        Velocity,
        Controllable,
        Render,
        Collidable,
        COUNT
    };

    /**
     * wrapper class for Attribute enum for conversion into unsigned
     * int
     */
    class AttrType
    {
    public:
        // constructor for attribute type enum
        AttrType(const Attribute &l_type): m_type(l_type) {}

        // conversion constructor
        AttrType(const unsigned int &l_int): m_type(static_cast<Attribute>(l_int)) {}

        // conversion operator
        operator unsigned int()
        {
            return static_cast<unsigned int>(m_type);
        }
    private:
        const Attribute m_type;
    };

}
