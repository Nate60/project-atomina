#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "render/GLRenderable.hpp"
#include "render/GLBuffer.hpp"
#include "render/GLBuffer.hpp"

namespace ATMA
{

    class AppWindow;

    /**
     * Abstract class of Graphics Rendering Context, used to draw drawable objects.
     * Must be pointed to an app window first.
     */
    class GLRenderContext
    {
    public:
        // default deconstructor
        virtual ~GLRenderContext();

        /**
         * Sets the size of the current view port that he render context is drawing to
         * @param l_size dimensions of the new viewport
         */
        virtual void setSize(const Vec2<unsigned int> &l_size) = 0;
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

    protected:
        // protected constructor so it cannot be publicly instantiated
        
        GLRenderContext();
        friend class AppWindow;
    };

}