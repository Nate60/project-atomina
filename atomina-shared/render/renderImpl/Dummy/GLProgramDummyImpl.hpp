#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "render/GLProgram.hpp"

namespace ATMA
{

    /**
     * @brief Dummy implementation of a shader program
     */
    class ATMA_API GLProgramDummyImpl: public GLProgram
    {
    public:
        // default constructor
        GLProgramDummyImpl();

        // default deconstructor
        virtual ~GLProgramDummyImpl();

        /**
         * @brief included compiled shader into the program
         * @param l_shader compiled shader
         */
        virtual void attachShader(const std::shared_ptr<GLShader> &l_shader);

        /**
         * @brief links all parts of the shader program to GL context
         */
        virtual void link();

        /**
         * @brief executes shader program
         */
        virtual void exec();

        /**
         * @brief sets a uniform value to a matrix
         * @param l_name name of the uniform in the shader program
         * @param l_mat matrix of values
         */
        virtual void setUniformMat3f(const std::string &l_name, const Mat3<float> &l_mat);
    };

}