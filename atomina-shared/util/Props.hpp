#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "util/AtominaException.hpp"

namespace ATMA
{

    /**
     * wrapper class for unordered map that holds string keys assigned to arbitrary
     * values, and can allow for case insensitivity
     */
    class ATMA_API Props
    {
    private:
        std::unordered_map<std::string, std::any> m_self{};
        bool m_caseSensitve{false};

        /**
         * helper function to check if the unordered map contains
         * the key
         * @param l_key key to check for
         * @returns if the key is contained in unordered map
         */
        bool hasKeyPostTransform(const std::string &l_key) const
        {
            auto itr = m_self.find(l_key);
            return !(itr == m_self.end());
        }
    public:
        /**
         * default constructor can specifiy if the object should
         * be case sensitive
         * @param l_isCaseSensitive toggle case sensitivity
         */
        Props(const bool &l_isCaseSensitive = false);

        /**
         * copy constructor
         * @param l_other existing properties object
         */
        Props(const Props &l_other);

        /**
         * move constructor
         * @param l_other existing r value reference
         */
        Props(Props &&l_other);

        /**
         * default destructor
         */
        virtual ~Props();

        /**
         * overloaded operator to acccess the inner unordered map
         * @param l_key string key to get value
         * @returns the associated any object containing the value
         */
        std::any &operator[](const std::string &l_key);

        /**
         * overloaded operator to access const values of inner map
         * @param l_key string key to get value
         * @returns the associated any object containing the value
         */
        const std::any &operator[](const std::string &l_key) const;

        /**
         * copy operator
         * @param l_other existing props object
         * @returns new props object from copied object
         */
        Props &operator=(const Props &l_other);

        /**
         * move operator
         * @param l_other existing r value reference props
         * @returns new props objects from moved object
         */
        Props &operator=(Props &&l_other);

        /**
         * gets the value from the associated key and type
         * casted to the template class
         * @tparam type to cast to
         * @param l_key key to get value from
         * @returns object from associated key type casted
         */
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

        /**
         * get value from key type casted, if the key has no value
         * return the other value given
         * @tparam type of the expected value and fallback value
         * @param l_key key to look for value with
         * @param l_other fallback value if key is not contain in map
         * @returns either the found value or if not found the fallback value
         */
        template<class T>
        const T &value_or(const std::string &l_key, const T &l_other) const
        {
            if(contains(l_key))
                return getAs<T>(l_key);
            else
                return l_other;
        }

        /**
         * removes the key and value from the map
         * @param l_key key to remove key value pair from map
         */
        void remove(const std::string &l_key);

        /**
         * checks to see if map contains the key
         * after case sentitivity is applied
         * @param l_key the key to check for
         * @returns if the key is found
         */
        bool contains(const std::string &l_key) const;
    };

}