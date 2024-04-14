#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "GLShader.hpp"
#include "math/Mat3.hpp"
#include "util/ATConst.hpp"

namespace ATMA
{

    /**
     * @brief Abstracts the shader program and holds its id reference
     */
    class ATMA_API GLProgram
    {
    public:
        // default deconstructor
        virtual ~GLProgram();

        /**
         * @brief factory function to create the pre-determined implementation type of shader
         * program
         * @return pointer to new shader program
         */
        static std::shared_ptr<GLProgram> makeProgram();

        /**
         * @brief included compiled shader into the program
         * @param l_shader compiled shader
         */
        virtual void attachShader(const std::shared_ptr<GLShader> &l_shader) = 0;

        /**
         * @brief links all parts of the shader program to GL context
         */
        virtual void link() = 0;

        /**
         * @brief executes shader program
         */
        virtual void exec() = 0;

        /**
         * @brief sets a uniform value to a matrix
         * @param l_name name of the uniform in the shader program
         * @param l_mat matrix of values
         */
        virtual void setUniformMat3f(const std::string &l_name, const Mat3<float> &l_mat) = 0;

        /**
         * Factory function for creating a Shader Program for the
         * platform
         * @returns Shader Program for the platform
        */
        static std::shared_ptr<GLProgram> makeDefaultProgram();
    protected:
        // default constructor, protected so it cannot be created outside the class
        GLProgram();
        unsigned int m_bindID;
    };

}