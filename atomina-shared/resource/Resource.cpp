#include "pch.hpp"
#include "Resource.hpp"

namespace ATMA
{
    Resource::Resource(const std::string &l_name, const Path &l_path, const unsigned int &l_type):
        m_name(l_name),
        m_path(l_path),
        m_type(l_type)
    {
    }

    Resource::Resource(const Resource &l_other): m_name(l_other.m_name), m_path(l_other.m_path), m_type(l_other.m_type)
    {
    }

    Resource::Resource(Resource &&l_other): m_name(l_other.m_name), m_path(l_other.m_path), m_type(l_other.m_type) {}

    void Resource::operator=(const Resource &l_other)
    {
        m_name = l_other.m_name;
        m_path = l_other.m_path;
        m_type = l_other.m_type;
    }

    void Resource::operator=(Resource &&l_other)
    {
        m_name = std::move(l_other.m_name);
        m_path = std::move(l_other.m_path);
        m_type = std::move(l_other.m_type);
    }

    Resource::~Resource() {}

    const std::string &Resource::name() const
    {
        return m_name;
    }

    const Path &Resource::path() const
    {
        return m_path;
    }

    const unsigned int &Resource::type() const
    {
        return m_type;
    }
}
