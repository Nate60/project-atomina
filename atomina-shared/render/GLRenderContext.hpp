#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "GUI/AppWindow.hpp"
#include "render/GLRenderable.hpp"
#include "render/GLBuffer.hpp"
#include "resource/graphics/Font.hpp"

namespace ATMA
{

    /**
     * Abstract class of Graphics Rendering Context, used to draw drawable objects.
     * Must be pointed to an app window first.
     */
    class ATMA_API GLRenderContext
    {
    public:
        // default deconstructor
        virtual ~GLRenderContext();

        /**
         * Points the render context to the corresponding app window to draraw to it
         * from now on
         * @param l_window the App window to target
         */
        virtual void setWindow(std::shared_ptr<AppWindow> l_window) = 0;

        /**
         * Sets the size of the current view port that he render context is drawing to
         * @param l_size dimensions of the new viewport
         */
        virtual void setSize(const Vec2<unsigned int> &l_size) = 0;

        virtual void setFont(const std::shared_ptr<Font> l_font);

        /**
         * Starts a draw call for the renderable object
         * @param l_renderable the object to be drawn
         */
        virtual void add(std::shared_ptr<GLRenderable> l_renderable);

        /**
         * Starts drawing text to the screen
         * @param l_text the text to be drawn
         */
        virtual void draw() = 0;

        /**
         * clears the view port that he Render context has been set to
         * to be all one colour
         */
        virtual void clear() = 0;

        /**
         * Factory function for creating a render context for the
         * platform
         * @returns unique pointer of the render context
         */
        static std::unique_ptr<GLRenderContext> makeRenderContext();
    protected:
        std::vector<std::shared_ptr<GLRenderable>> m_elementContainer{};
        std::priority_queue<
            std::shared_ptr<GLRenderable>,
            std::vector<std::shared_ptr<GLRenderable>>,
            GLRenderableCompare>
            m_elementStack{m_elementContainer.begin(), m_elementContainer.end(), GLRenderableCompare()};
        std::shared_ptr<Font> m_font;
        // protected constructor so it cannot be publicly instantiated
        GLRenderContext();
    };

}