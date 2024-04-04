#ifdef _WINDOWS
#    pragma once
#    include "pch.hpp"
#    include "core/api.hpp"
#    include "util/ATConst.hpp"
#    include "GUI/AppWindow.hpp"
#    include "GUI/window/WindowWinImpl.hpp"
#    include "render/GLProgram.hpp"
#    include "render/GLRenderContext.hpp"
#    include "math/MathFuncs.hpp"

namespace ATMA
{

    /**
     * Windows Specific OpenGL implementation of Graphic Render Context
     */
    class ATMA_API GLRenderContextOpenGLWinImpl: public GLRenderContext
    {
    public:
        // default deconstructor
        virtual ~GLRenderContextOpenGLWinImpl();

        // default constructor
        GLRenderContextOpenGLWinImpl();

        /**
         * sets render context to target the given app window
         * @param l_window app window for the render context to target
         */
        virtual void setWindow(std::shared_ptr<AppWindow> l_window) override;

        /**
         * Sets the size of the current view port that he render context is drawing to
         * @param l_size dimensions of the new viewport
         */
        virtual void setSize(const Vec2<unsigned int> &l_size) override;

        /**
         * Starts a draw call for the renderable object
         * @param l_renderable the object to be drawn
         */
        virtual void draw(std::shared_ptr<GLRenderable> l_renderable) override;

        /**
         * clears the view port that he Render context has been set to
         * to be all one colour
         */
        virtual void clear() override;
    protected:
        // device context handle
        HDC m_hdc;
        // GL Render Context handle
        HGLRC m_hglrc;
    };

}
#else
#    error Windows implementation included in non-Windows target
#endif