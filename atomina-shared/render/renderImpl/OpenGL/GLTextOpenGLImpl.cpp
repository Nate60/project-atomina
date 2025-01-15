#include "pch.hpp"
#include "GLTextOpenGLImpl.hpp"

namespace ATMA
{
    // TODO: Make Texture sub-class Font and make these attributes ATMA-44
    static const int constexpr GLYPH_SIZE = 32;
    static const int constexpr GLYPHS_PER_ROW = 11;

    void GLTextOpenGLImpl::draw(const Props &l_props)
    {
        if(m_prog == nullptr || m_texture == nullptr)
        {
            ATMA_ENGINE_WARN("Drawing Renderable without texture or program");
            return;
        }
        float advance = 0;
        m_prog->exec();
        m_texture->bind();
        for(auto &c: m_text)
        {
            // set uniforms
            m_prog->setUniformMat3f("u_camera", l_props.value_or<Mat3<float>>("u_camera", identityMatrix<float>()));
            m_prog->setUniformMat3f("u_translate", translationMatrix(m_pos.x + advance, m_pos.y));
            m_prog->setUniformMat3f("u_scale", scalingMatrix(m_size.x, m_size.y));
            m_prog->setUniformMat3f("u_rot", rotationMatrix(m_rot));
            m_prog->setUniformMat3f("u_textureRegion", scalingMatrix<float>(GLYPH_SIZE, GLYPH_SIZE));
            m_prog->setUniformMat3f(
                "u_texturePos",
                translationMatrix<float>((c % GLYPHS_PER_ROW) * GLYPH_SIZE, (c / GLYPHS_PER_ROW) * GLYPH_SIZE)
            );
            m_prog->setUniformMat3f("u_textureCamera", m_texture->m_texture.m_proj);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            advance += m_size.x * 2; // I dont' understand why times 2
        }
    }

}