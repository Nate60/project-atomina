#include "pch.hpp"
#include "Shader.hpp"

namespace ATMA
{

    // constructor specifying name
    Shader::Shader(const std::string &l_name): Resource(l_name)
    {
#ifdef ATMA_USE_OPENGL
        m_self = std::make_shared<ShaderBindingGLADImpl>(ATConst::DEFAULT_SHADER_PATH);
#endif
    }

    // constructor specifying name and filename;
    Shader::Shader(const std::string &l_name, const std::string &l_filename):
        Resource(l_name, l_filename)
    {
#ifdef ATMA_USE_OPENGL
        m_self = std::make_shared<ShaderBindingGLADImpl>(l_filename);
#endif
    }

    void Shader::compile(const ShaderType &l_type)
    {
        m_self->compile(l_type);
    }

    const unsigned int &Shader::getBindID() const
    {
        return m_self->getBindID();
    }
}