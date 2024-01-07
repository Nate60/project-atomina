#include "pch.hpp"
#include "GLProgramOpenGLImpl.hpp"

namespace ATMA
{
    GLProgramOpenGLImpl::GLProgramOpenGLImpl()
    {
        m_bindID = glCreateProgram();
    }

    GLProgramOpenGLImpl::~GLProgramOpenGLImpl()
    {
        glDeleteProgram(m_bindID);
    }

    void GLProgramOpenGLImpl::attachShader(const std::shared_ptr<GLShader> &l_shader)
    {
        glAttachShader(m_bindID, l_shader->getBindID());
    }

    void GLProgramOpenGLImpl::link()
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

    void GLProgramOpenGLImpl::exec()
    {
        glUseProgram(m_bindID);
    }

    void GLProgramOpenGLImpl::setUniformMat3f(const std::string &l_name, const Mat3<float> &l_mat)
    {
        int location = glGetUniformLocation(m_bindID, l_name.c_str());
        glUniformMatrix3fv(location, 1, GL_TRUE, &(l_mat.m_values[0][0]));
    }

}