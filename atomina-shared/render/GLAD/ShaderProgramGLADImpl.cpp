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

    void ShaderProgramGLADImpl::setUniformMat3f(const std::string &l_name, const Mat3<float> &l_mat)
    {
        int location = glGetUniformLocation(m_bindID, l_name.c_str());
        glUniformMatrix3fv(location, 1, GL_TRUE, &(l_mat.m_values[0][0]));
    }

}