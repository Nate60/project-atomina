#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "render/ShaderBinding.hpp"

namespace ATMA
{
    using namespace std::string_literals;

    /**
     * @brief OpenGL specific implementation of Shader
     */
    class ATMA_API ShaderBindingGLADImpl: public ShaderBinding
    {
    public:
        // constructor with name and filename of resource
        ShaderBindingGLADImpl(const std::string &l_fileName);

        // default deconstructor
        virtual ~ShaderBindingGLADImpl();

        /**
         * @brief compiles the source code in the specified filename
         * @param l_type expected type of shader to be compiled
         */
        virtual void compile(ShaderType l_type) override;
    protected:
        std::string m_shaderText = ""s;
    };

}