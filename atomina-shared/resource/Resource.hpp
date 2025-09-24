#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "util/Path.hpp"

namespace ATMA
{
    /**
     * base resource pure virtual class for containing files
     * located on the system and loading them into memory
     */
    struct Resource
    {
    public:
        // constructor defining name, path, and type of resource
        Resource(const std::string &l_name, const Path &l_path, const unsigned int &l_type);

        // Copy constructor
        Resource(const Resource &l_other);

        // Move constructor
        Resource(Resource &&l_other);

        // destructor
        virtual ~Resource();

        // Copy operator
        void operator=(const Resource &l_other);

        // Move operator
        void operator=(Resource &&l_other);

        const std::string &name() const;
        const Path &path() const;
        const unsigned int &type() const;

        friend inline std::ostream &operator<<(std::ostream &os, const Resource &res);
    protected:
        std::string m_name;
        Path m_path;
        unsigned int m_type;
    };

    /**
     * interface for loaded resources so the can be managed
     * by the context
     */
    struct LoadedResource
    {
    };

    /**
     * resource logging formatting func
     * @param os output stream to pipe into
     * @param res resource object to log
     */
    inline std::ostream &operator<<(std::ostream &os, const Resource &res)
    {
        return os << res.m_name;
    }
}
