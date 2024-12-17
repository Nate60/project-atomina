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

        // constructor specifying IP
        URL(const std::string &l_url = std::string{"127.0.0.1"});

        // deconstructor
        virtual ~URL();

        /**
         * @brief copy operator
         * @param l_other URL to copy
         * @return copied URL
         */
        URL &operator=(const URL &l_other);

        /**
         * @brief move operator
         * @param l_other URL to move
         * @return moved operator
         */
        URL &operator=(URL &&l_other);

        /**
         * @brief getter for ip string
         * @return ip as string
         */
        const std::string &getIP() const;
    protected:
        std::string m_addr;
    };

}