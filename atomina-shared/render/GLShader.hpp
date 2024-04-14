#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "util/Log.hpp"
#include "util/Path.hpp"

namespace ATMA
{

    enum class ShaderType
    {
        None = 0,
        Vertex,
        Fragment
    };

    /**
     * @brief Reference to Shader code that can be executed on GPU
     */
    class ATMA_API GLShader
    {
    public:
        // default deconstructor
        virtual ~GLShader();

        /**
         * @brief compiles the shader source using GL context
         * @param l_type expected type of the shader being compiled
         */
        virtual void compile(ShaderType l_type) = 0;

        /**
         * @brief gets the reference id of the shader from the GL context
         * @return id of the shader
         */
        const unsigned int &getBindID() const;

        /**
         * Factory function for creating shaders
         * @param l_filePath path to file on system
         * @returns Graphics shader for the platform
        */
        static std::shared_ptr<GLShader> makeShader(const Path &l_filePath);
    protected:
        // constructor with  filename of resource
        GLShader(const Path &l_filePath);

        Path m_shaderFile;
        unsigned int m_bindID;
    };

}