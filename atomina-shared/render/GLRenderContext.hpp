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
         * @brief get render context singleton. Singleton because uses global openGLfunctions
         * @return pointer to new shader program
         */
        static std::shared_ptr<GLRenderContext> getRenderContext();


        /**
         * Context is created on first get, but that may not be when we want to initialize the
         * GLLibrary Context. For example GLEW requires that a window is created first
         */
        virtual void init() = 0;

        /**
         * Sets the size of the current view port that he render context is drawing to
         * @param l_size dimensions of the new viewport
         */
        virtual void setViewPort(const Vec2<int> &l_pos, const Vec2<int> &l_size) = 0;


        /**
         * clears the view port that he Render context has been set to
         * to be all one colour
         */
        virtual void clear() = 0;

        /**
         * toggles rendering blends
         */
        virtual void toggleBlend(const bool &l_toggle) = 0;

    protected:
        // protected constructor so it cannot be publicly instantiated
        
        GLRenderContext();
        friend class AppWindow;
    };

}