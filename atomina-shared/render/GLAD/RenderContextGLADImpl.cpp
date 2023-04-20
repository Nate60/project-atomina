#include "pch.hpp"
#include "RenderContextGLADImpl.hpp"

namespace ATMA
{

    RenderContextGLADImpl::RenderContextGLADImpl(): RenderContext() {}

    RenderContextGLADImpl::~RenderContextGLADImpl() {}

    void RenderContextGLADImpl::draw(
        const std::shared_ptr<VertexArray> &l_vertArray,
        const std::shared_ptr<IndexBuffer> &l_indexBuffer,
        const std::shared_ptr<ShaderProgram> &l_shaderProg
    ) const
    {
        l_vertArray->bind();
        l_indexBuffer->bind();
        l_shaderProg->exec();

        // bind textures on corresponding texture units
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

    void RenderContextGLADImpl::draw(
        const std::shared_ptr<Texture> &l_texture,
        const std::shared_ptr<ShaderProgram> l_shaderProg
    ) const
    {
        l_texture->bind();
        l_shaderProg->exec();

        // bind textures on corresponding texture units
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

    void RenderContextGLADImpl::draw(
        const std::shared_ptr<Texture> &l_texture,
        const Vec2<float> &l_pos,
        const Vec2<float> &l_size,
        const float &l_rot
    ) const
    {
        std::shared_ptr<ShaderProgram> shaderprog = ShaderProgram::makeDefaultProgram();
        shaderprog->exec();
        auto transform = translationMatrix(l_pos.x, l_pos.y) * scalingMatrix(l_size.x, l_size.y)
                       * rotationMatrix(l_rot);
        shaderprog->setUniformMat3f("u_transform", transform);
        l_texture->bind();
        shaderprog->exec();

        // bind textures on corresponding texture units
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

    void RenderContextGLADImpl::drawText(
        const std::string &l_text,
        const Vec2<float> &l_pos,
        const Vec2<float> &l_size,
        const float &l_rot
    ) const
    {
        float advance = 0;
        std::shared_ptr<ShaderProgram> shaderprog = ShaderProgram::makeDefaultProgram();
        shaderprog->exec();

        for(auto &c: l_text)
        {
            auto transform = translationMatrix(l_pos.x + advance, l_pos.y)
                           * scalingMatrix(l_size.x, l_size.y) * rotationMatrix(l_rot);
            shaderprog->setUniformMat3f("u_transform", transform);
            m_font->bindCharacter(c);
            shaderprog->exec();
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            advance += l_size.x;
        }
    }

}