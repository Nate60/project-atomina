#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "render/GLAD/ShaderBindingGLADImpl.hpp"
#include "resource/Resource.hpp"
#include "util/ATConst.hpp"

namespace ATMA
{

    class ATMA_API Shader: public Resource
    {
    public:
        // constructor specifying name
        Shader(const std::string &l_name);

        // constructor specifying name and filename;
        Shader(const std::string &l_name, const std::string &l_filename);

        void compile(const ShaderType &m_type);

        /**
         * @brief gets the reference id of the shader from the GL context
         * @return id of the shader
         */
        const unsigned int &getBindID() const;
    protected:
        std::shared_ptr<ShaderBinding> m_self;
    };

}