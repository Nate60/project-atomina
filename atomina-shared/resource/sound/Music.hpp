#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "SoundProperties.hpp"
#include "resource/Resource.hpp"

namespace ATMA
{

    /**
     * Implementation of Resource for music files 
     */
    class ATMA_API Music: public Resource
    {
    public:

        //constructor specifying name
        Music(const std::string &l_name);
    
        //constructor specifying name and filename
        Music(const std::string &l_name, const std::string &l_filename);
    
        //deconstructor
        ~Music();
    };

}