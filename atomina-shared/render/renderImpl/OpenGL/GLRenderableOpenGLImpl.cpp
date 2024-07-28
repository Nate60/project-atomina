#include "pch.hpp"
#include "GLRenderableOpenGLImpl.hpp"

namespace ATMA
{

    void GLRenderableOpenGLImpl::draw(const Props &l_props)
    {
        if(m_prog == nullptr || m_texture == nullptr)
        {
            //Cant draw without a shader program or a texture
            return;
        }
            m_prog->exec();
            m_texture->bind();
            //set uniforms
            m_prog->setUniformMat3f("u_camera", l_props.value_or<Mat3<float>>("u_camera", identityMatrix<float>()));
            m_prog->setUniformMat3f("u_translate", translationMatrix(m_pos.x, m_pos.y));
            m_prog->setUniformMat3f("u_scale", scalingMatrix(m_size.x, m_size.y) );
            m_prog->setUniformMat3f("u_rot", rotationMatrix(m_rot));
            m_prog->setUniformMat3f("u_sourceRegion", identityMatrix<float>());
            m_prog->setUniformMat3f("u_sourcePos", identityMatrix<float>());
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

}