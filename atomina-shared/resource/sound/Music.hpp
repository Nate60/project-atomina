#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "SoundProperties.hpp"
#include "resource/Resource.hpp"

namespace ATMA
{

    class ATMA_API Music: public Resource
    {
    public:
        Music(const std::string &l_name);
        Music(const std::string &l_name, const std::string &l_filename);
        ~Music();
    };

}