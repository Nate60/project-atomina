#include "pch.hpp"
#include "URL.hpp"

namespace ATMA
{
    URL::URL() noexcept: m_addr("127.0.0.1") {}

    URL::URL(const std::string &l_url) noexcept: m_addr(l_url) {}

    URL::URL(const URL &l_url) noexcept: m_addr(l_url.m_addr) {}

    URL::URL(URL &&l_url) noexcept: m_addr(std::move(l_url.m_addr)) {}

    URL::~URL() {}
}