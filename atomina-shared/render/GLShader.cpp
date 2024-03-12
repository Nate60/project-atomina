#include "pch.hpp"
#include "GLShader.hpp"
#ifdef ATMA_OPENGL
#    include "render/renderImpl/OpenGL/GLShaderOpenGLImpl.hpp"
#    define __ATMAMAKEGLSHADER(shaderFile) return std::make_shared<GLShaderOpenGLImpl>(shaderFile)
#else
#    include "render/renderImpl/Dummy/GLShaderDummyImpl.hpp"
#    define __ATMAMAKEGLSHADER(shaderFile) return std::make_shared<GLShaderDummyImpl>(shaderFile)
#endif
namespace ATMA
{

    GLShader::GLShader(const Path &l_filePath): m_shaderFile(l_filePath) {}

    GLShader::~GLShader() {}

    const unsigned int &GLShader::getBindID() const
    {
        return m_bindID;
    }

    std::shared_ptr<GLShader> GLShader::makeShader(const Path &l_filePath)
    {
        __ATMAMAKEGLSHADER(l_filePath);
    }
}