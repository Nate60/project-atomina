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

}