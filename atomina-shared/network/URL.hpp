#pragma once
#include "pch.hpp"
#include "core/api.hpp"

namespace ATMA
{

    /**
     * @brief Class for holding addresses of remote connections
     */
    class ATMA_API URL
    {
    public:
        // default constructor
        URL();

        // constructor specifying IP
        URL(const std::string &l_url);

        // deconstructor
        ~URL();

        URL &operator=(const URL &l_other);

        URL &operator=(URL &&l_other);

        const std::string &getIP() const;
    protected:
        std::string m_addr;
    };

}