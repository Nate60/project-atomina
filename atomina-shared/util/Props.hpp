#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "util/AtominaException.hpp"

namespace ATMA
{

    class ATMA_API Props
    {
    private:
        std::unordered_map<std::string, std::any> m_self{};
        bool m_caseSensitve{false};

        bool hasKeyPostTransform(const std::string &l_key) const
        {
            auto itr = m_self.find(l_key);
            return !(itr == m_self.end());
        }
    public:
        Props(const bool &l_isCaseSensitive = false);
        Props(const Props &l_other);
        Props(Props &&l_other);
        ~Props();

        std::any &operator[](const std::string &l_key);

        Props &operator=(const Props &l_other);
        Props &operator=(Props &&l_other);

        template<class T>
        const T &getAs(const std::string &l_key) const
        {
            if(!m_caseSensitve)
            {
                auto newKey = l_key;
                std::transform(newKey.begin(), newKey.end(), newKey.begin(), ::toupper);
                if(hasKeyPostTransform(newKey))
                    return std::any_cast<const T &>(m_self.find(newKey)->second);
                else
                    throw ValueNotFoundException("Properites does not contain key " + newKey);
            }
            else
            {
                if(hasKeyPostTransform(l_key))
                    return std::any_cast<const T &>(m_self.find(l_key)->second);
                else
                    throw ValueNotFoundException("Properites does not contain key " + l_key);
            }
        }

        template<class T>
        const T &value_or(const std::string &l_key, const T &l_other) const
        {
            if(contains(l_key))
                return getAs<T>(l_key);
            else
             return l_other;
        }

        void remove(const std::string &l_key);

        bool contains(const std::string &l_key) const;
    };

}