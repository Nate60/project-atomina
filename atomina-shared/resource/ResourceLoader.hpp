#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "util/Path.hpp"
#include "ResourceEnum.hpp"
#include "util/AtominaException.hpp"

namespace ATMA
{

    /**
     * interface class for acquirable resource loaders by the engine
     */
    template<class T>
    class ResourceLoader
    {
    public:

        /**
        * factory function for creating class subtype resource
        * @param l_name name of resource
        * @param l_path file path to resource
        * @return shared pointer to resource
        */
        std::shared_ptr<T> load(const std::string &l_name, const Path &l_path)
        {
            return std::make_shared<T>(l_name, l_path, ResType(ResourceEnum::None));
        }
                
        /**
        * factory function for creating class subtype resource
        * @param l_name name of resource
        * @return shared pointer to resource
        */
        std::shared_ptr<T> load(const std::string &l_name)
        {
            throw ResourceAcquisitionException("Empty Resource cannot be loaded with path");
        }

        //default constructor
        ResourceLoader() {}

        //deconstructor
        virtual ~ResourceLoader() {}
    };

}