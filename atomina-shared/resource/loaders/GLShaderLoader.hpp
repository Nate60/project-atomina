#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "resource/ResourceLoader.hpp"
#include "render/GLShader.hpp"

namespace ATMA
{
    template<>
    class ResourceLoader<GLShader>
    {
    public:
        ResourceLoader();
        virtual ~ResourceLoader();
        /**
         * factory function for creating Shader resource
         * @param l_ctx Engine Context
         * @param l_name name of resource
         * @param l_path file path to resource
         * #param l_buffer containing resource data
         * @param l_bytes number of bytes consumed
         * @return shared pointer to resource
         */
        std::shared_ptr<GLShader> load(
            ATMAContext *l_ctx,
            const std::string &l_name,
            const Path &l_path,
            std::vector<char> &l_buffer,
            size_t &l_bytes
        );
        std::shared_ptr<GLShader> load(ATMAContext *l_ctx, const std::string &l_name);
    };
}
