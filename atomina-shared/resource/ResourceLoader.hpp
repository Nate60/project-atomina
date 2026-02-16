#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "util/Path.hpp"
#include "ResourceEnum.hpp"
#include "util/AtominaException.hpp"

namespace ATMA
{

    class ATMAContext;

    /**
     * interface class for acquirable resource loaders by the engine
     */
    template<class T>
    class ResourceLoader
    {
    public:
        /**
         * factory function for creating class subtype resource
         * @param l_ctx Engine Context
         * @param l_name name of resource
         * @param l_path file path to resource
         * #param l_buffer containing resource data
         * @param l_bytes number of bytes consumed
         * @return shared pointer to resource
         */
        std::shared_ptr<T> load(
            ATMAContext *l_ctx,
            const std::string &l_name,
            const Path &l_path,
            std::vector<char> &l_buffer,
            size_t &l_bytes
        )
        {
            return T{l_name, l_buffer, ResType(ResourceEnum::None)};
        }

        /**
         * factory function for creating class subtype resource
         * @param l_name name of resource
         * @return shared pointer to resource
         */
        std::shared_ptr<T> load(ATMAContext *l_ctx, const std::string &l_name)
        {
            throw ResourceAcquisitionException("Empty Resource cannot be loaded without path");
        }

        // default constructor
        ResourceLoader() {}

        // deconstructor
        virtual ~ResourceLoader() {}
    };

}
