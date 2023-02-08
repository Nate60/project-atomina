#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "render/RenderContext.hpp"
#include "util/Log.hpp"
#include "GUI/Window.hpp"

namespace ATMA
{

    /**
     * @brief OpenGL specific implementation of Render Context
     */
    class ATMA_API RenderContextGLADImpl: public RenderContext
    {
    public:
        // default constructor
        RenderContextGLADImpl();

        // default deconstructor
        virtual ~RenderContextGLADImpl();

        /**
         * @brief passes corresponding buffers to GL context and then draws
         * @param l_vertArray Vertex Array containing layouts
         * @param l_indexBuffer describes order of indicies
         * @param l_shaderProg shader program with linked shaders
         */
        virtual void draw(
            const std::shared_ptr<VertexArray> &l_vertArray,
            const std::shared_ptr<IndexBuffer> &l_indexBuffer,
            const std::shared_ptr<ShaderProgram> &l_shaderProg
        ) const override;
    };

}