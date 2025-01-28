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

    GLShader::GLShader(const Shader &l_shader): m_shader(l_shader), LoadedResource() {}

    GLShader::~GLShader() {}

    const unsigned int &GLShader::getBindID() const
    {
        return m_bindID;
    }

    std::shared_ptr<GLShader> GLShader::makeShader(const Shader &l_shader)
    {
        __ATMAMAKEGLSHADER(l_shader);
    }
}