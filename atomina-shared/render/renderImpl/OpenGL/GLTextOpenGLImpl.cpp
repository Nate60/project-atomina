#include "pch.hpp"
#include "GLTextOpenGLImpl.hpp"

namespace ATMA
{
    //TODO: Make Texture sub-class Font and make these attributes ATMA-44
    static const int constexpr GLYPH_SIZE = 32;
    static const float constexpr SHEET_SIZE_X = GLYPH_SIZE * 11;
    static const float constexpr SHEET_SIZE_Y = GLYPH_SIZE * 12;
    static const float constexpr GLYPH_SIZE_RATIO_X = GLYPH_SIZE / SHEET_SIZE_X;
    static const float constexpr GLYPH_SIZE_RATIO_Y = GLYPH_SIZE / SHEET_SIZE_Y;

    void GLTextOpenGLImpl::draw(const Props &l_props)
    {
        float advance = 0;
        m_prog->exec();
        m_texture->bind();
        for(auto &c: m_text)
        {
            //set uniforms
            m_prog->setUniformMat3f("u_camera", l_props.value_or<Mat3<float>>("u_camera", identityMatrix<float>()));
            m_prog->setUniformMat3f("u_translate", translationMatrix(m_pos.x + advance, m_pos.y));
            m_prog->setUniformMat3f("u_scale", scalingMatrix(m_size.x, m_size.y) );
            m_prog->setUniformMat3f("u_rot", rotationMatrix(m_rot));
            m_prog->setUniformMat3f("u_sourceRegion", scalingMatrix(GLYPH_SIZE_RATIO_X, GLYPH_SIZE_RATIO_Y));
            m_prog->setUniformMat3f("u_sourcePos", translationMatrix((c % 11) * GLYPH_SIZE_RATIO_X -1.f, (c / 11) * GLYPH_SIZE_RATIO_Y - 1.f));
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            advance += m_size.x * 2; // I dont' understand why times 2
        }
    }

}