#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "render/ShaderProgram.hpp"

namespace ATMA
{

    /**
     * @brief OpenGL implementation of a shader program
     */
    class ATMA_API ShaderProgramGLADImpl: public ShaderProgram
    {
    public:
        // default constructor
        ShaderProgramGLADImpl();

        // default deconstructor
        virtual ~ShaderProgramGLADImpl();

        /**
         * @brief included compiled shader into the program
         * @param l_shader compiled shader
         */
        virtual void attachShader(const std::shared_ptr<Shader> &l_shader);

        /**
         * @brief links all parts of the shader program to GL context
         */
        virtual void link();

        /**
         * @brief executes shader program
         */
        virtual void exec();
    };

}