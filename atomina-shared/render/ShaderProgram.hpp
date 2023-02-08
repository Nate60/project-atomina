#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "resource/graphics/Shader.hpp"

namespace ATMA
{

    /**
     * @brief Abstracts the shader program and holds its id reference
     */
    class ATMA_API ShaderProgram
    {
    public:
        // default constructor
        ShaderProgram();

        // default deconstructor
        virtual ~ShaderProgram();

        /**
         * @brief factory function to create the pre-determined implementation type of shader
         * program
         * @return pointer to new shader program
         */
        static std::shared_ptr<ShaderProgram> makeProgram();

        /**
         * @brief included compiled shader into the program
         * @param l_shader compiled shader
         */
        virtual void attachShader(const std::shared_ptr<Shader> &l_shader) = 0;

        /**
         * @brief links all parts of the shader program to GL context
         */
        virtual void link() = 0;

        /**
         * @brief executes shader program
         */
        virtual void exec() = 0;
    protected:
        unsigned int m_bindID;
    };

}