#pragma once
#include "pch.hpp"
#include "core/api.hpp"

namespace ATMA
{

    /**
     * @brief Class for holding addresses of remote connections
     */
    class URL
    {
    public:
        // default constructor
        URL() noexcept;

        // constructor specifying IP
        URL(const std::string &l_url) noexcept;

        // copy constructor
        URL(const URL &l_url) noexcept;

        // move constructor
        URL(URL &&l_url) noexcept;

        // deconstructor
        virtual ~URL();

        /**
         * @brief copy operator
         * @param l_other URL to copy
         * @return copied URL
         */
        inline URL &operator=(const URL &l_other) noexcept
        {
            m_addr = l_other.m_addr;
            return *this;
        }

        /**
         * @brief move operator
         * @param l_other URL to move
         * @return moved operator
         */
        inline URL &operator=(URL &&l_other) noexcept
        {
            m_addr = std::move(l_other.m_addr);
            return *this;
        }

        /**
         * @brief getter for ip string
         * @return ip as string
         */
        inline const std::string &getIP() const
        {
            return m_addr;
        }
    protected:
        std::string m_addr;
    };

}