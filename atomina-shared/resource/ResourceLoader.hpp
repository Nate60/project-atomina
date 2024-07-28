#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "util/Path.hpp"
#include "ResourceEnum.hpp"
#include "util/AtominaException.hpp"

namespace ATMA
{

    /**
     * interface class for acquirable resource by the engine
     */
    template<class T>
    class ResourceLoader
    {
    public:
        std::shared_ptr<T> load(const std::string &l_name, const Path &l_path) 
        {
            return std::make_shared<T>(l_name, l_path, ResType(ResourceEnum::None));
        }

        std::shared_ptr<T> load(const std::string& l_name)
        {
            throw ResourceAcquisitionException("Empty Resource cannot be loaded with path");
        }

        ResourceLoader() {}
        virtual ~ResourceLoader() {}
    };

}