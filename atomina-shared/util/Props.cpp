#include "pch.hpp"
#include "Props.hpp"

namespace ATMA
{

    Props::Props(const bool &l_isCaseSensitive): m_caseSensitve(l_isCaseSensitive) {}

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

    std::any &Props::operator[](const std::string &l_key)
    {
        if(!m_caseSensitve)
        {
            auto newKey = l_key;
            std::transform(newKey.begin(), newKey.end(), newKey.begin(), ::toupper);
            return m_self[newKey];
        }
        else
            return m_self[l_key];
    }

    Props &Props::operator=(const Props &l_other)
    {
        m_self = l_other.m_self;
        m_caseSensitve = l_other.m_caseSensitve;
        return *this;
    }

    Props &Props::operator=(Props &&l_other)
    {
        m_self = std::move(l_other.m_self);
        m_caseSensitve = std::move(l_other.m_caseSensitve);
        return *this;
    }

    void Props::remove(const std::string &l_key)
    {
        if(!m_caseSensitve)
        {
            auto newKey = l_key;
            std::transform(newKey.begin(), newKey.end(), newKey.begin(), ::toupper);
            auto itr = m_self.find(newKey);
            if(itr == m_self.end())
            {
                throw ValueNotFoundException("Properites does not contain key " + newKey);
            }
            else
            {
                m_self.erase(itr);
            }
        }
        else
        {
            auto itr = m_self.find(l_key);
            if(itr == m_self.end())
            {
                throw ValueNotFoundException("Properites does not contain key " + l_key);
            }
            else
            {
                m_self.erase(itr);
            }
        }
    }

    bool Props::contains(const std::string &l_key) const
    {
        if(!m_caseSensitve)
        {
            auto newKey = l_key;
            std::transform(newKey.begin(), newKey.end(), newKey.begin(), ::toupper);
            return hasKeyPostTransform(newKey);
        }
        else
        {
            return hasKeyPostTransform(l_key);
        }
    }

}