#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "resource/graphics/Shader.hpp"

namespace ATMA
{
    using namespace std::string_literals;

    /**
     * @brief OpenGL specific implementation of Shader
     */
    class ATMA_API ShaderGLADImpl: public Shader
    {
    public:
        // constructor specifying name
        ShaderGLADImpl(const std::string &l_name);

        // constructor with name and filename of resource
        ShaderGLADImpl(const std::string &l_name, const std::string &l_fileName);

        // default deconstructor
        virtual ~ShaderGLADImpl();

        /**
         * @brief compiles the source code in the specified filename
         * @param l_type expected type of shader to be compiled
         */
        virtual void compile(ShaderType l_type) override;
    protected:
        std::string m_shaderText = ""s;
    };

}