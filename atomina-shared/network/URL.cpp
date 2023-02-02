#include "pch.hpp"
#include "URL.hpp"

namespace ATMA
{
    URL::URL(): m_addr("127.0.0.1") {}

    URL::URL(const std::string &l_url): m_addr(l_url) {}

    URL::~URL() {}

    const std::string &URL::getIP() const
    {
        return m_addr;
    }

    URL &URL::operator=(const URL &l_other)
    {
        m_addr = l_other.m_addr;
        return *this;
    }

    URL &URL::operator=(URL &&l_other)
    {
        m_addr = std::move(l_other.m_addr);
        return *this;
    }
}