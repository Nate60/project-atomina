#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "render/GLShader.hpp"

namespace ATMA
{

    /**
     * @brief Dummy implementation of Shader
     */
    class ATMA_API GLShaderDummyImpl: public GLShader
    {
    public:
        // constructor with name and filename of resource
        GLShaderDummyImpl(const std::string &l_fileName);

        // default deconstructor
        virtual ~GLShaderDummyImpl();

        /**
         * @brief compiles the source code in the specified filename
         * @param l_type expected type of shader to be compiled
         */
        virtual void compile(ShaderType l_type) override;
    protected:
        std::string m_shaderText;
    };

}