#pragma once
#include "core/api.hpp"

namespace ATMA
{

    using AttributeType = unsigned int;

    enum class ATMA_API Attribute
    {
        None = 0,
        Translatable,
        Drawable,
        Controllable,
        Animatable,
        COUNT
    };

    class ATMA_API AttrType
    {
    public:
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
