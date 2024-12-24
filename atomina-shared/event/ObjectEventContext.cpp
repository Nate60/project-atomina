#include "pch.hpp"
#include "ObjectEventContext.hpp"

namespace ATMA
{
    ObjectEventContext::ObjectEventContext(const unsigned int &l_objectEventType, const Props &l_props):
        m_objectEventType(l_objectEventType),
        m_properties(l_props)
    {
    }

    ObjectEventContext::~ObjectEventContext() {}

}