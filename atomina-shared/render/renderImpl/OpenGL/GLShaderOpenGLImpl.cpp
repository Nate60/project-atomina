#include "pch.hpp"
#include "GLShaderOpenGLImpl.hpp"

namespace ATMA
{
    using namespace std::string_literals;

    GLShaderOpenGLImpl::GLShaderOpenGLImpl(const std::string &l_fileName): GLShader(l_fileName)
    {
        m_bindID = 0u;
    }

    GLShaderOpenGLImpl::~GLShaderOpenGLImpl()
    {
        glDeleteShader(m_bindID);
    }

    void GLShaderOpenGLImpl::compile(ShaderType l_type)
    {

        switch(l_type)
        {
        case ShaderType::Vertex:
            m_bindID = glCreateShader(GL_VERTEX_SHADER);
            break;
        case ShaderType::Fragment:
            m_bindID = glCreateShader(GL_FRAGMENT_SHADER);
            break;
        }
        m_shaderText = ""s;
        std::ifstream l_fileStream{m_shaderFile};
        std::string sourceLine;
        while(std::getline(l_fileStream, sourceLine))
            m_shaderText += sourceLine + "\n";
        l_fileStream.close();
        const char *l_shaderText = m_shaderText.c_str();
        glShaderSource(m_bindID, 1, &l_shaderText, NULL);
        glCompileShader(m_bindID);
        int success;
        char infoLog[1024];
        glGetShaderiv(m_bindID, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(m_bindID, 1024, NULL, infoLog);
            ATMA_ENGINE_ERROR(
                "Error with compiling shader: {0} [OPENGL]: {1}", m_shaderFile, infoLog
            );
        }
    }
}
