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

    Resource::~Resource()
    {}

}