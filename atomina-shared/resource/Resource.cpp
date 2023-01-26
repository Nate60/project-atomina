#include "pch.hpp"
#include "Resource.hpp"

namespace ATMA
{
    Resource::Resource(const std::string &l_name): m_resourceName(l_name) {}

    Resource::Resource(const std::string &l_name, const std::string &l_filename):
        m_resourceName(l_name)
    {
    }

    Resource::~Resource() {}

}