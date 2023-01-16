#pragma once
#include "core/api.hpp"

namespace ATMA
{

    using ObjectEventID = unsigned int;

    /**
     * All possible internal object event types 
     */
    enum class ATMA_API ObjectEvent
    {
        None = 0u,
        ShutDown,
        MousePressed,
        MouseReleased,
        MouseOver,
        COUNT
    };

    /**
     * wrapper class for easy conversion from Object Event Type enum to
     * unsigned int 
     */
    class ATMA_API ObjectEventType
    {
    public:

        //constructor specifying enum type
        ObjectEventType(const ObjectEvent &l_type): m_type(l_type) {}

        // conversion constructor
        ObjectEventType(const unsigned int &l_int): m_type(static_cast<ObjectEvent>(l_int)) {}

        // conversion operator
        operator unsigned int()
        {
            return static_cast<unsigned int>(m_type);
        }
    private:
        const ObjectEvent m_type;
    };

}