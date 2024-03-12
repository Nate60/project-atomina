#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "render/GLShader.hpp"

namespace ATMA
{

    /**
     * @brief OpenGL specific implementation of Shader
     */
    class ATMA_API GLShaderOpenGLImpl: public GLShader
    {
    public:
        // constructor with name and filename of resource
        GLShaderOpenGLImpl(const Path &l_filePath);

        // default deconstructor
        virtual ~GLShaderOpenGLImpl();

        /**
         * @brief compiles the source code in the specified filename
         * @param l_type expected type of shader to be compiled
         */
        virtual void compile(ShaderType l_type) override;
    protected:
        std::string m_shaderText;
    };

}