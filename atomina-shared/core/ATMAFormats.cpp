#include "event/ObjectEventContext.hpp"
#include "pch.hpp"
#include "ATMAFormats.hpp"
#include "resource/Resource.hpp"
#include <memory>

namespace ATMA
{

    using namespace std::string_literals;

    std::ostream &operator<<(std::ostream &os, const std::shared_ptr<AttrBase> a)
    {
        return os << a->m_attrTypeName;
    }

    std::ostream &operator<<(std::ostream &os, const std::shared_ptr<SysBase> s)
    {
        return os << s->m_sysTypeName;
    }

    std::ostream &operator<<(std::ostream &os, const std::shared_ptr<Resource> r)
    {
        return os << r->m_resourceName;
    }

    std::ostream &operator<<(std::ostream &os, const ObjectEventContext &e)
    {
        return os << e.m_properties.value_or("name", "[null]"s);
    }

}