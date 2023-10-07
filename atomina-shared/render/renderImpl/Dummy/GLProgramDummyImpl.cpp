#include "pch.hpp"
#include "GLProgramDummyImpl.hpp"

namespace ATMA
{
    GLProgramDummyImpl::GLProgramDummyImpl()
    {
        m_bindID = 0u;
    }

    GLProgramDummyImpl::~GLProgramDummyImpl() {}

    void GLProgramDummyImpl::attachShader(const std::shared_ptr<GLShader> &l_shader) {}

    void GLProgramDummyImpl::link() {}

    void GLProgramDummyImpl::exec() {}

    void GLProgramDummyImpl::setUniformMat3f(const std::string &l_name, const Mat3<float> &l_mat) {}

}