#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "render/Buffer.hpp"
#include "render/ShaderProgram.hpp"

namespace ATMA
{
    class Window;

    /**
     * @brief Abstraction of GL Context for making draw calls
     */
    class ATMA_API RenderContext
    {
    public:
        // default constructor
        RenderContext();

        // default deconstructor
        virtual ~RenderContext();

        /**
         * @brief factory function to make render context of the pre-determined implementation type
         * @return render context of correct type
         */
        static std::unique_ptr<RenderContext> makeRenderContext();

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
        ) const = 0;
    };

}