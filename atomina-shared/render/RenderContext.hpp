#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "render/Buffer.hpp"
#include "render/ShaderProgram.hpp"
#include "resource/graphics/Texture.hpp"
#include "resource/graphics/Font.hpp"

namespace ATMA
{
    class Window;

    using namespace std::string_literals;

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

        virtual void setFont(std::shared_ptr<Font> l_font);

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

        virtual void draw(
            const std::shared_ptr<Texture> &l_texture,
            const std::shared_ptr<ShaderProgram> l_prog = ShaderProgram::makeDefaultProgram()
        ) const = 0;

        virtual void draw(
            const std::shared_ptr<Texture> &l_texture,
            const Vec2<float> &l_pos,
            const Vec2<float> &l_size = Vec2<float>{1, 1},
            const float &l_rot = 0
        ) const = 0;

        virtual void drawText(
            const std::string &l_text,
            const Vec2<float> &l_pos,
            const Vec2<float> &l_size = Vec2<float>{1, 1},
            const float &l_rot = 0
        ) const = 0;
    protected:
        // GLFW Context is non-existent on startup so font cannot be created right away
        std::shared_ptr<Font> m_font = nullptr;
    };

}