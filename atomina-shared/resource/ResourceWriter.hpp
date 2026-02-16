#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "util/Path.hpp"
#include "util/Log.hpp"

namespace ATMA
{

    /**
     * interface class for writable resource
     */
    template<class T>
    class ResourceWriter
    {
    public:
        /**
         * write resource to filesystem
         * @param l_name name of resource
         * @param l_path file path to resource
         * @return shared pointer to resource
         */
        void write(const std::shared_ptr<T> res, const Path &l_path)
        {
            ATMA_ENGINE_WARN("Called resource writer with no target resource (default implementation is empty)");
        }

        // default constructor
        ResourceWriter() {}

        // deconstructor
        virtual ~ResourceWriter() {}
    };

}
