#include "pch.hpp"
#include "ObjectEventContext.hpp"

namespace ATMA
{
    ObjectEventContext::ObjectEventContext(const unsigned int &l_objectEventType):
        m_objectEventType(l_objectEventType)
    {
    }

    ObjectEventContext::~ObjectEventContext() {}

}