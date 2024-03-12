#include "pch.hpp"
#include "GLShaderDummyImpl.hpp"

namespace ATMA
{
    using namespace std::string_literals;

    GLShaderDummyImpl::GLShaderDummyImpl(const Path &l_filePath): GLShader(l_filePath)
    {
        m_bindID = 0u;
    }

    GLShaderDummyImpl::~GLShaderDummyImpl() {}

    void GLShaderDummyImpl::compile(ShaderType l_type)
    {

        m_shaderText = ""s;
        std::ifstream l_fileStream{m_shaderFile.toString()};
        std::string sourceLine;
        while(std::getline(l_fileStream, sourceLine))
            m_shaderText += sourceLine + "\n";
        l_fileStream.close();
    }
}