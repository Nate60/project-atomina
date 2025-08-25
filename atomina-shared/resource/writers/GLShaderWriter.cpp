#include "pch.hpp"
#include "GLShaderWriter.hpp"

namespace ATMA
{
    ResourceWriter<GLShader>::ResourceWriter() {}

    ResourceWriter<GLShader>::~ResourceWriter() {}

    void ResourceWriter<GLShader>::write(const std::shared_ptr<GLShader> l_res, const Path &l_path)
    {
        std::basic_ofstream<char> shaderFile{l_path.toString()};
        shaderFile.exceptions(std::ios::failbit | std::ios::badbit);
        shaderFile << l_res->m_shader.m_source;
        shaderFile.close();
        ATMA_ENGINE_INFO("wrote {}", l_path.toString().c_str());
    }

}
