#pragma once
#include "pch.hpp"
#include "core/api.hpp"

namespace ATMA
{

    /**
     * interface class for acquirable resource by the engine 
     */
    class ATMA_API Resource
    {
    public:
    const std::string m_resourceName;
        
        //constructor with name
        Resource(const std::string &l_name);

        //constructor with name and filename of resource
        Resource(const std::string &l_name, const std::string &l_fileName);

        //deconstructor
        ~Resource();
    };

    //equality operator
    inline bool operator==(const Resource &a, const Resource &b);

}