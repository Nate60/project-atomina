#include "pch.hpp"
#include "Props.hpp"

namespace ATMA
{

    Props::Props(const bool &l_isCaseSensitive): m_caseSensitve(l_isCaseSensitive) {}

    Props::Props(const std::map<std::string,std::any> &l_values, const bool &l_isCaseSensitive):
        m_caseSensitve(l_isCaseSensitive)
    {
        for (const auto& v : l_values)
        {
            if(!m_caseSensitve)
            {
                auto newKey = v.first;
                std::transform(newKey.begin(), newKey.end(), newKey.begin(), ::toupper);
                m_self[newKey] = v.second;
            }
            else
                m_self[v.first] = v.second;
        }
    }

    Props::Props(const Props &l_other)
    {
        m_self = l_other.m_self;
        m_caseSensitve = l_other.m_caseSensitve;
    }

    Props::Props(Props &&l_other)
    {
        m_self = std::move(l_other.m_self);
        m_caseSensitve = std::move(l_other.m_caseSensitve);
    }

    Props::~Props() {}

}