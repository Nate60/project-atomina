#include "pch.hpp"
#include "Shader.hpp"

namespace ATMA
{

    using namespace std::string_literals;

    Shader::Shader(const std::string &l_name): Resource(l_name), m_shaderFile("") {}

    Shader::Shader(const std::string &l_name, const std::string &l_fileName):
        Resource(l_name, l_fileName),
        m_shaderFile(l_fileName)
    {
    }

    Shader::~Shader() {}

    void Shader::compile(ShaderType l_type)
    {
        ATMA_ENGINE_WARN("Compile called for Super class Shader");
    }

    const unsigned int &Shader::getBindID() const
    {
        return m_bindID;
    }

}