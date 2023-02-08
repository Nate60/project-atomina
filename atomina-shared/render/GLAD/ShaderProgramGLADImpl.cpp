#include "pch.hpp"
#include "ShaderProgramGLADImpl.hpp"

namespace ATMA
{
    ShaderProgramGLADImpl::ShaderProgramGLADImpl()
    {
        m_bindID = glCreateProgram();
    }

    ShaderProgramGLADImpl::~ShaderProgramGLADImpl()
    {
        glDeleteProgram(m_bindID);
    }

    void ShaderProgramGLADImpl::attachShader(const std::shared_ptr<Shader> &l_shader)
    {
        glAttachShader(m_bindID, l_shader->getBindID());
    }

    void ShaderProgramGLADImpl::link()
    {
        int success;
        char infoLog[2048];
        glLinkProgram(m_bindID);
        glGetProgramiv(m_bindID, GL_LINK_STATUS, &success);

        if(!success)
        {
            glGetProgramInfoLog(m_bindID, 2048, NULL, infoLog);
            ATMA_ENGINE_ERROR("Error with linking program [OPENGL]: {0}", infoLog);
        }
    }

    void ShaderProgramGLADImpl::exec()
    {
        glUseProgram(m_bindID);
    }
}