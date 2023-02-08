#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "resource/Resource.hpp"
#include "util/Log.hpp"

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
    class ATMA_API Shader: public Resource
    {
    public:
        // constructor specifying name
        Shader(const std::string &l_name);

        // constructor with name and filename of resource
        Shader(const std::string &l_name, const std::string &l_fileName);

        // default deconstructor
        virtual ~Shader();

        /**
         * @brief compiles the shader source using GL context
         * @param l_type expected type of the shader being compiled
         */
        virtual void compile(ShaderType l_type);

        /**
         * @brief gets the reference id of the shader from the GL context
         * @return id of the shader
         */
        const unsigned int &getBindID() const;
    protected:
        std::string m_shaderFile;
        unsigned int m_bindID;
    };

}